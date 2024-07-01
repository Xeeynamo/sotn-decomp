/* Mednafen - Multi-system Emulator
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* TODO:
	Note to self: Emulating the SPU at more timing accuracy than sample, and emulating the whole SPU RAM write port FIFO thing and hypothetical periodic FIFO commit to
	SPU RAM(maybe every 32 CPU cycles, with exceptions?) will likely necessitate a much more timing-accurate CPU core, and emulation of the SPU delay register(or at least the
	effects of the standard value written to it), to avoid game glitches.  Probably more trouble than it's worth....

	SPU IRQ emulation isn't totally correct, behavior is kind of complex; run more tests on PS1.

	Test reverb upsampler on the real thing.

	Alter reverb algorithm to process in the pattern of L,R,L,R,L,R on each input sample, instead of doing both L and R on every 2 input samples(make
   sure the real thing does it this way too, I think it at least runs the downsampler this way).

	Alter reverb algorithm to perform saturation more often, as occurs on the real thing.

	See if sample flag & 0x8 does anything weird, like suppressing the program-readable block end flag setting.

	Determine the actual purpose of global register 0x2C(is it REALLY an address multiplier?  And if so, does it affect the reverb offsets too?)

	For ADSR and volume sweep, should the divider be reset to 0 on &0x8000 == true, or should the upper bit be cleared?

	Should shift occur on all stages of ADPCM sample decoding, or only at the end?

	On the real thing, there's some kind of weirdness with ADSR when you voice on when attack_rate(raw) = 0x7F; the envelope level register is repeatedly
	reset to 0, which you can see by manual writes to the envelope level register.  Normally in the attack phase when attack_rate = 0x7F, enveloping is 		effectively stuck/paused such that the value you write is sticky and won't be replaced or reset.  Note that after you voice on, you can write a new 		attack_rate < 0x7F, and enveloping will work "normally" again shortly afterwards.  You can even write an attack_rate of 0x7F at that point to pause 		enveloping 		clocking.  I doubt any games rely on this, but it's something to keep in mind if we ever need greater insight as to how the SPU 	functions at a low-level in 		order to emulate it at cycle granularity rather than sample granularity, and it may not be a bad idea to 		investigate this oddity further and emulate it in 		the future regardless.

	Voice 1 and 3 waveform output writes to SPURAM might not be correct(noted due to problems reading this area of SPU RAM on the real thing
	based on my expectations of how this should work).
*/

/*
 Notes:

	All addresses(for 16-bit access, at least) within the SPU address space appear to be fully read/write as if they were RAM, though
	values at some addresses(like the envelope current value) will be "overwritten" by the sound processing at certain times.

	32-bit and 8-bit reads act as if it were RAM(not tested with all addresses, but a few, assuming the rest are the same), but 8-bit writes
	to odd addresses appear to be ignored, and 8-bit writes to even addresses are treated as 16-bit writes(most likely, but, need to code custom assembly to
	fully test the upper 8 bits).  NOTE: the preceding information doesn't necessarily cover accesses with side effects, they still need to be tested; and it
	of course covers reads/writes from the point of view of software running on the CPU.

	It doesn't appear to be possible to enable FM on the first channel/voice(channel/voice 0).

	Lower bit of channel start address appears to be masked out to 0(such that ADPCM block decoding is always 8 16-bit units, 16 bytes, aligned), as far as
	block-decoding and flag-set program-readable loop address go.
*/

/*
 Update() isn't called on Read and Writes for performance reasons, it's called with sufficient granularity from the event
 system, though this will obviously need to change if we ever emulate the SPU with better precision than per-sample(pair).
*/

//#include "psx.h"
//#include "cdc.h"
#include "spu.h"
#include <assert.h>
#include <string.h>

#define INLINE inline
#define NO_INLINE
#define MDFN_UNLIKELY

enum
{
    IRQ_SPU
};

void IRQ_Assert(int /*which*/, bool /*asserted*/)
{

}

static INLINE void clamp(int32_t *val, int32_t min, int32_t max)
{
    if (*val < min)
        *val = min;
    if (*val > max)
        *val = max;
}

//#include <libretro.h>

//#include "../state_helpers.h"

uint32_t IntermediateBufferPos;
int16_t IntermediateBuffer[4096][2];

//#define SPUIRQ_DBG(format, ...) { printf("[SPUIRQDBG] " format " -- Voice 22 CA=0x%06x,LA=0x%06x\n", ## __VA_ARGS__, Voices[22].CurAddr, Voices[22].LoopAddr); }

static INLINE void SPUIRQ_DBG(const char *fmt, ...)
{
}

static const int16 FIR_Table[256][4] =
{
#include "spu_fir_table.inc"
};

PS_SPU::PS_SPU()
{
   IntermediateBufferPos = 0;
   memset(IntermediateBuffer, 0, sizeof(IntermediateBuffer));

}

PS_SPU::~PS_SPU()
{
}

void PS_SPU::Power(void)
{
   clock_divider = 768;

   memset(SPURAM, 0, sizeof(SPURAM));

   for(int i = 0; i < 24; i++)
   {
      memset(Voices[i].DecodeBuffer, 0, sizeof(Voices[i].DecodeBuffer));
      Voices[i].DecodeM2 = 0;
      Voices[i].DecodeM1 = 0;

      Voices[i].DecodePlayDelay = 0;
      Voices[i].DecodeWritePos = 0;
      Voices[i].DecodeReadPos = 0;
      Voices[i].DecodeAvail = 0;

      Voices[i].DecodeShift = 0;
      Voices[i].DecodeWeight = 0;
      Voices[i].DecodeFlags = 0;

      Voices[i].IgnoreSampLA = false;

      Voices[i].Sweep[0].Power();
      Voices[i].Sweep[1].Power();

      Voices[i].Pitch = 0;
      Voices[i].CurPhase = 0;

      Voices[i].StartAddr = 0;

      Voices[i].CurAddr = 0;

      Voices[i].ADSRControl = 0;

      Voices[i].LoopAddr = 0;

      Voices[i].PreLRSample = 0;

      memset(&Voices[i].ADSR, 0, sizeof(SPU_ADSR));
   }

   GlobalSweep[0].Power();
   GlobalSweep[1].Power();

   NoiseDivider = 0;
   NoiseCounter = 0;
   LFSR = 0;

   FM_Mode = 0;
   Noise_Mode = 0;
   Reverb_Mode = 0;
   ReverbWA = 0;

   ReverbVol[0] = ReverbVol[1] = 0;

   CDVol[0] = CDVol[1] = 0;

   ExternVol[0] = ExternVol[1] = 0;

   IRQAddr = 0;

   RWAddr = 0;

   SPUControl = 0;

   VoiceOn = 0;
   VoiceOff = 0;

   BlockEnd = 0;

   CWA = 0;

   memset(Regs, 0, sizeof(Regs));

   memset(RDSB, 0, sizeof(RDSB));

   memset(RUSB, 0, sizeof(RUSB));
   RvbResPos = 0;

   ReverbCur = ReverbWA;

   IRQAsserted = false;
}

static INLINE void CalcVCDelta(const uint8 zs, uint8 speed, bool log_mode, bool dec_mode, bool inv_increment, int16 Current, int &increment, int &divinco)
{
   increment = (7 - (speed & 0x3));

   if(inv_increment)
      increment = ~increment;

   divinco = 32768;

   if(speed < 0x2C)
      increment = (unsigned)increment << ((0x2F - speed) >> 2);

   if(speed >= 0x30)
      divinco >>= (speed - 0x2C) >> 2;

   if(log_mode)
   {
      if(dec_mode)	// Log decrement mode
         increment = (Current * increment) >> 15;
      else			// Log increment mode
      {
         if((Current & 0x7FFF) >= 0x6000)
         {
            if(speed < 0x28)
               increment >>= 2;
            else if(speed >= 0x2C)
               divinco >>= 2;
            else	// 0x28 ... 0x2B
            {
               increment >>= 1;
               divinco >>= 1;
            }
         }
      }
   } // end if(log_mode)

   if(divinco == 0 && speed < zs) //0x7F)
      divinco = 1;
}


INLINE void SPU_Sweep::Power(void)
{
   Control = 0;
   Current = 0;
   Divider = 0;
}

INLINE void SPU_Sweep::WriteControl(uint16 value)
{
   Control = value;
}

INLINE int16 SPU_Sweep::ReadVolume(void)
{
   return((int16)Current);
}

void SPU_Sweep::Clock()
{
   const bool log_mode = (bool)(Control & 0x4000);
   const bool dec_mode = (bool)(Control & 0x2000);
   const bool inv_mode = (bool)(Control & 0x1000);
   const bool inv_increment = (dec_mode ^ inv_mode) | (dec_mode & log_mode);
   const uint16 vc_cv_xor = (inv_mode & !(dec_mode & log_mode)) ? 0xFFFF : 0x0000;
   const uint16 TestInvert = inv_mode ? 0xFFFF : 0x0000;
   int increment;
   int divinco;

   CalcVCDelta(0x7F, Control & 0x7F, log_mode, dec_mode, inv_increment, (int16)(Current ^ vc_cv_xor), increment, divinco);
   //printf("%d %d\n", divinco, increment);

   if((dec_mode & !(inv_mode & log_mode)) && ((Current & 0x8000) == (inv_mode ? 0x0000 : 0x8000) || (Current == 0)))
   {
      //
      // Not sure if this condition should stop the Divider adding or force the increment value to 0.
      //
      Current = 0;
   }
   else
   {
      Divider += divinco;

      if(Divider & 0x8000)
      {
         Divider = 0;

         if(dec_mode || ((Current ^ TestInvert) != 0x7FFF))
         {
            uint16 PrevCurrent = Current;
            Current = Current + increment;

            //printf("%04x %04x\n", PrevCurrent, Current);

            if(!dec_mode && ((Current ^ PrevCurrent) & 0x8000) && ((Current ^ TestInvert) & 0x8000))
               Current = 0x7FFF ^ TestInvert;
         }
      }
   }
}

INLINE void SPU_Sweep::WriteVolume(int16 value)
{
   Current = value;
}


//
// Take care not to trigger SPU IRQ for the next block before its decoding start.
//
void PS_SPU::RunDecoder(SPU_Voice *voice)
{
   // 5 through 0xF appear to be 0 on the real thing.
   static const int32 Weights[16][2] =
   {
      // s-1    s-2
      {   0,    0 },
      {  60,    0 },
      { 115,  -52 },
      {  98,  -55 },
      { 122,  -60 },
   };

   if(voice->DecodeAvail >= 11)
   {
      if(SPUControl & 0x40)
      {
         unsigned test_addr = (voice->CurAddr - 1) & 0x3FFFF;
         if(IRQAddr == test_addr || IRQAddr == (test_addr & 0x3FFF8))
         {
            //SPUIRQ_DBG("SPU IRQ (VDA): 0x%06x", addr);
            IRQAsserted = true;
            IRQ_Assert(IRQ_SPU, IRQAsserted);
         }
      }
      return;
   }

   if((voice->CurAddr & 0x7) == 0)
   {
      // Handle delayed flags from the previously-decoded block.
      //
      // NOTE: The timing of setting the BlockEnd bit here, and forcing ADSR envelope volume to 0, is a bit late.  (And I'm not sure if it should be done once
      // per decoded block, or more than once, but that's probably not something games would rely on, but we should test it anyway).
      //
      // Correctish timing can be achieved by moving this block of code up above voice->DecodeAvail >= 11, and sticking it inside an: if(voice->DecodeAvail <= 12),
      // though more tests are needed on the ADPCM decoding process as a whole before we should actually make such a change.  Additionally, we'd probably
      // have to separate the CurAddr = LoopAddr logic, so we don't generate spurious early SPU IRQs.
      if(voice->DecodeFlags & 0x1)
      {
         voice->CurAddr = voice->LoopAddr & ~0x7;

         BlockEnd |= 1 << (voice - Voices);

         if(!(voice->DecodeFlags & 0x2))	// Force enveloping to 0 if not "looping".  TODO: Should we reset the ADSR divider counter too?
         {
            if(!(Noise_Mode & (1 << (voice - Voices))))
            {
               voice->ADSR.Phase = ADSR_RELEASE;
               voice->ADSR.EnvLevel = 0;
            }
         }
      }
   }

   //for(int z = 0; z < 4; z++)
   {

      if(SPUControl & 0x40)
      {
         unsigned test_addr = voice->CurAddr & 0x3FFFF;
         if(IRQAddr == test_addr || IRQAddr == (test_addr & 0x3FFF8))
         {
            //SPUIRQ_DBG("SPU IRQ: 0x%06x", addr);
            IRQAsserted = true;
            IRQ_Assert(IRQ_SPU, IRQAsserted);
         }
      }

      if((voice->CurAddr & 0x7) == 0)
      {
         const uint16 CV = SPURAM[voice->CurAddr];
         voice->DecodeShift = CV & 0xF;
         voice->DecodeWeight = (CV >> 4) & 0xF;
         voice->DecodeFlags = (CV >> 8) & 0xFF;

         if(voice->DecodeFlags & 0x4)
         {
            if(!voice->IgnoreSampLA)
               voice->LoopAddr = voice->CurAddr;
#if 0
            else
            {
               if(voice->LoopAddr != voice->CurAddr)
               {
                  PSX_DBG(PSX_DBG_FLOOD, "[SPU] Ignore: LoopAddr=0x%08x, SampLA=0x%08x\n", voice->LoopAddr, voice->CurAddr);
               }
            }
#endif
         }
         voice->CurAddr = (voice->CurAddr + 1) & 0x3FFFF;
      }

      //
      // Don't else this block; we need to ALWAYS decode 4 samples per call to RunDecoder() if DecodeAvail < 11, or else sample playback
      // at higher rates will fail horribly.
      //
      {
         const int32 weight_m1 = Weights[voice->DecodeWeight][0];
         const int32 weight_m2 = Weights[voice->DecodeWeight][1];
         uint16 CV;
         unsigned shift;
         uint32 coded;
         int16 *tb = &voice->DecodeBuffer[voice->DecodeWritePos];

         CV = SPURAM[voice->CurAddr];
         shift = voice->DecodeShift;

         if(MDFN_UNLIKELY(shift > 12))
         {
            //PSX_DBG(PSX_DBG_FLOOD, "[SPU] Buggy/Illegal ADPCM block shift value on voice %u: %u\n", (unsigned)(voice - Voices), shift);

            shift = 8;
            CV &= 0x8888;
         }

         coded = (uint32)CV << 12;


         for(int i = 0; i < 4; i++)
         {
            int32 sample = (int16)(coded & 0xF000) >> shift;

            sample += ((voice->DecodeM2 * weight_m2) >> 6);
            sample += ((voice->DecodeM1 * weight_m1) >> 6);

            clamp(&sample, -32768, 32767);

            tb[i] = sample;
            voice->DecodeM2 = voice->DecodeM1;
            voice->DecodeM1 = sample;
            coded >>= 4;
         }
         voice->DecodeWritePos = (voice->DecodeWritePos + 4) & 0x1F;
         voice->DecodeAvail += 4;
         voice->CurAddr = (voice->CurAddr + 1) & 0x3FFFF;
      }
   }
}

void PS_SPU::CacheEnvelope(SPU_Voice *voice)
{
   uint32_t   raw    = voice->ADSRControl;
   SPU_ADSR *ADSR    = &voice->ADSR;
   int32_t     Sl    = (raw >> 0) & 0x0F;
   int32_t     Dr    = (raw >> 4) & 0x0F;
   int32_t     Ar    = (raw >> 8) & 0x7F;

   int32_t     Rr    = (raw >> 16) & 0x1F;
   int32_t     Sr    = (raw >> 22) & 0x7F;

   ADSR->AttackExp   = (bool)(raw & (1 << 15));
   ADSR->ReleaseExp  = (bool)(raw & (1 << 21));
   ADSR->SustainExp  = (bool)(raw & (1 << 31));
   ADSR->SustainDec  = (bool)(raw & (1 << 30));

   ADSR->AttackRate  = Ar;
   ADSR->DecayRate   = Dr << 2;
   ADSR->SustainRate = Sr;
   ADSR->ReleaseRate = Rr << 2;

   ADSR->SustainLevel = (Sl + 1) << 11;
}

void PS_SPU::ResetEnvelope(SPU_Voice *voice)
{
   SPU_ADSR *ADSR = &voice->ADSR;

   ADSR->EnvLevel = 0;
   ADSR->Divider = 0;
   ADSR->Phase = ADSR_ATTACK;
}

void PS_SPU::ReleaseEnvelope(SPU_Voice *voice)
{
   SPU_ADSR *ADSR = &voice->ADSR;

   ADSR->Divider = 0;
   ADSR->Phase = ADSR_RELEASE;
}


void PS_SPU::RunEnvelope(SPU_Voice *voice)
{
   SPU_ADSR *ADSR = &voice->ADSR;
   int increment;
   int divinco;
   int16 uoflow_reset;

   if(ADSR->Phase == ADSR_ATTACK && ADSR->EnvLevel == 0x7FFF)
      ADSR->Phase++;

   //static INLINE void CalcVCDelta(const uint8 zs, uint8 speed, bool log_mode, bool decrement, bool inv_increment, int16 Current, int &increment, int &divinco)
   switch(ADSR->Phase)
   {
      default: assert(0);
               break;

      case ADSR_ATTACK:
               CalcVCDelta(0x7F, ADSR->AttackRate, ADSR->AttackExp, false, false, (int16)ADSR->EnvLevel, increment, divinco);
               uoflow_reset = 0x7FFF;
               break;

      case ADSR_DECAY:
               CalcVCDelta(0x1F << 2, ADSR->DecayRate, true, true, true, (int16)ADSR->EnvLevel, increment, divinco);
               uoflow_reset = 0;
               break;

      case ADSR_SUSTAIN:
               CalcVCDelta(0x7F, ADSR->SustainRate, ADSR->SustainExp, ADSR->SustainDec, ADSR->SustainDec, (int16)ADSR->EnvLevel, increment, divinco);
               uoflow_reset = ADSR->SustainDec ? 0 : 0x7FFF;
               break;

      case ADSR_RELEASE:
               CalcVCDelta(0x1F << 2, ADSR->ReleaseRate, ADSR->ReleaseExp, true, true, (int16)ADSR->EnvLevel, increment, divinco);
               uoflow_reset = 0;
               break;
   }

   ADSR->Divider += divinco;
   if(ADSR->Divider & 0x8000)
   {
      const uint16 prev_level = ADSR->EnvLevel;

      ADSR->Divider = 0;
      ADSR->EnvLevel += increment;

      if(ADSR->Phase == ADSR_ATTACK)
      {
         // If previous the upper bit was 0, but now it's 1, handle overflow.
         if(((prev_level ^ ADSR->EnvLevel) & ADSR->EnvLevel) & 0x8000)
            ADSR->EnvLevel = uoflow_reset;
      }
      else
      {
         if(ADSR->EnvLevel & 0x8000)
            ADSR->EnvLevel = uoflow_reset;
      }
      if(ADSR->Phase == ADSR_DECAY && (uint16)ADSR->EnvLevel < ADSR->SustainLevel)
         ADSR->Phase++;
   }
}

INLINE void PS_SPU::CheckIRQAddr(uint32 addr)
{
   if(SPUControl & 0x40)
   {
      if(IRQAddr != addr)
         return;

      //SPUIRQ_DBG("SPU IRQ (ALT): 0x%06x", addr);
      IRQAsserted = true;
      IRQ_Assert(IRQ_SPU, IRQAsserted);
   }
}

INLINE void PS_SPU::WriteSPURAM(uint32 addr, uint16 value)
{
   CheckIRQAddr(addr);

   SPURAM[addr] = value;
}

INLINE uint16 PS_SPU::ReadSPURAM(uint32 addr)
{
   CheckIRQAddr(addr);
   return(SPURAM[addr]);
}

static INLINE int16 ReverbSat(int32 samp)
{
 if(samp > 32767)
  samp = 32767;

 if(samp < -32768)
  samp = -32768;

 return(samp);
}


INLINE uint32 PS_SPU::Get_Reverb_Offset(uint32 in_offset)
{
 uint32 offset = ReverbCur + (in_offset & 0x3FFFF);

 offset += ReverbWA & ((int32)(offset << 13) >> 31);
 offset &= 0x3FFFF;

 // For debugging in case there are any problems with games misprogramming the reverb registers in a race-conditiony manner that
 // causes important data in SPU RAM to be trashed:
 //if(offset < ReverbWA)
 // printf("BARF: offset=%05x reverbwa=%05x reverbcur=%05x in_offset=%05x\n", offset, ReverbWA, ReverbCur, in_offset & 0x3FFFF);

 return(offset);
}

int16 NO_INLINE PS_SPU::RD_RVB(uint16 raw_offs, int32 extra_offs)
{
 return ReadSPURAM(Get_Reverb_Offset((raw_offs << 2) + extra_offs));
}

void NO_INLINE PS_SPU::WR_RVB(uint16 raw_offs, int16 sample)
{
   WriteSPURAM(Get_Reverb_Offset(raw_offs << 2), sample);
}

//
// Zeroes optimized out; middle removed too(it's 16384)
static const int16 ResampTable[20] =
{
 -1, 2, -10, 35, -103, 266, -616, 1332, -2960, 10246, 10246, -2960, 1332, -616, 266, -103, 35, -10, 2, -1,
};

static INLINE int32 Reverb4422(const int16 *src)
{
 int32 out = 0;	// 32-bits is adequate(it won't overflow)

 for(unsigned i = 0; i < 20; i++)
  out += ResampTable[i] * src[i * 2];

 // Middle non-zero
 out += 0x4000 * src[19];

 out >>= 15;

 clamp(&out, -32768, 32767);

 return(out);
}

static INLINE int32 Reverb2244(const int16 *src)
{
   unsigned i;
   int32_t out = 0; /* 32bits is adequate (it won't overflow) */

   for(i = 0; i < 20; i++)
   out += ResampTable[i] * src[i];

   out >>= 14;

   clamp(&out, -32768, 32767);

   return out;
}

static int32 IIASM(const int16 IIR_ALPHA, const int16 insamp)
{
   if(MDFN_UNLIKELY(IIR_ALPHA == -32768))
   {
      if(insamp == -32768)
         return 0;
      return insamp * -65536;
   }

   return insamp * (32768 - IIR_ALPHA);
}

//
// Take care to thoroughly test the reverb resampling code when modifying anything that uses RvbResPos.
//
void PS_SPU::RunReverb(const int32* in, int32* out)
{
   unsigned lr;
 int32 upsampled[2];

 upsampled[0] = upsampled[1] = 0;

 for(lr = 0; lr < 2; lr++)
 {
  RDSB[lr][RvbResPos | 0x00] = in[lr];
  RDSB[lr][RvbResPos | 0x40] = in[lr];	// So we don't have to &/bounds check in our MAC loop
 }

 if(RvbResPos & 1)
 {
  int32 downsampled[2];

  for(unsigned lr = 0; lr < 2; lr++)
   downsampled[lr] = Reverb4422(&RDSB[lr][(RvbResPos - 39) & 0x3F]);

  /* Run algorithm */
  if(SPUControl & 0x80)
  {
   int16 ACC0, ACC1;
   int16 FB_A0, FB_A1, FB_B0, FB_B1;

   int16 IIR_INPUT_A0 = ReverbSat(((RD_RVB(IIR_SRC_A0) * IIR_COEF) >> 15) + ((downsampled[0] * IN_COEF_L) >> 15));
   int16 IIR_INPUT_A1 = ReverbSat(((RD_RVB(IIR_SRC_A1) * IIR_COEF) >> 15) + ((downsampled[1] * IN_COEF_R) >> 15));
   int16 IIR_INPUT_B0 = ReverbSat(((RD_RVB(IIR_SRC_B0) * IIR_COEF) >> 15) + ((downsampled[0] * IN_COEF_L) >> 15));
   int16 IIR_INPUT_B1 = ReverbSat(((RD_RVB(IIR_SRC_B1) * IIR_COEF) >> 15) + ((downsampled[1] * IN_COEF_R) >> 15));

   int16 IIR_A0 = ReverbSat((((IIR_INPUT_A0 * IIR_ALPHA) >> 14) + (IIASM(IIR_ALPHA, RD_RVB(IIR_DEST_A0, -1)) >> 14)) >> 1);
   int16 IIR_A1 = ReverbSat((((IIR_INPUT_A1 * IIR_ALPHA) >> 14) + (IIASM(IIR_ALPHA, RD_RVB(IIR_DEST_A1, -1)) >> 14)) >> 1);
   int16 IIR_B0 = ReverbSat((((IIR_INPUT_B0 * IIR_ALPHA) >> 14) + (IIASM(IIR_ALPHA, RD_RVB(IIR_DEST_B0, -1)) >> 14)) >> 1);
   int16 IIR_B1 = ReverbSat((((IIR_INPUT_B1 * IIR_ALPHA) >> 14) + (IIASM(IIR_ALPHA, RD_RVB(IIR_DEST_B1, -1)) >> 14)) >> 1);

   WR_RVB(IIR_DEST_A0, IIR_A0);
   WR_RVB(IIR_DEST_A1, IIR_A1);
   WR_RVB(IIR_DEST_B0, IIR_B0);
   WR_RVB(IIR_DEST_B1, IIR_B1);

   ACC0 = ReverbSat((((RD_RVB(ACC_SRC_A0) * ACC_COEF_A) >> 14) +
	   	     ((RD_RVB(ACC_SRC_B0) * ACC_COEF_B) >> 14) +
	   	     ((RD_RVB(ACC_SRC_C0) * ACC_COEF_C) >> 14) +
	   	     ((RD_RVB(ACC_SRC_D0) * ACC_COEF_D) >> 14)) >> 1);

   ACC1 = ReverbSat((((RD_RVB(ACC_SRC_A1) * ACC_COEF_A) >> 14) +
	   	     ((RD_RVB(ACC_SRC_B1) * ACC_COEF_B) >> 14) +
	   	     ((RD_RVB(ACC_SRC_C1) * ACC_COEF_C) >> 14) +
	   	     ((RD_RVB(ACC_SRC_D1) * ACC_COEF_D) >> 14)) >> 1);

   FB_A0 = RD_RVB(MIX_DEST_A0 - FB_SRC_A);
   FB_A1 = RD_RVB(MIX_DEST_A1 - FB_SRC_A);
   FB_B0 = RD_RVB(MIX_DEST_B0 - FB_SRC_B);
   FB_B1 = RD_RVB(MIX_DEST_B1 - FB_SRC_B);

   WR_RVB(MIX_DEST_A0, ReverbSat(ACC0 - ((FB_A0 * FB_ALPHA) >> 15)));
   WR_RVB(MIX_DEST_A1, ReverbSat(ACC1 - ((FB_A1 * FB_ALPHA) >> 15)));

   WR_RVB(MIX_DEST_B0, ReverbSat(((FB_ALPHA * ACC0) >> 15) - ((FB_A0 * (int16)(0x8000 ^ FB_ALPHA)) >> 15) - ((FB_B0 * FB_X) >> 15)));
   WR_RVB(MIX_DEST_B1, ReverbSat(((FB_ALPHA * ACC1) >> 15) - ((FB_A1 * (int16)(0x8000 ^ FB_ALPHA)) >> 15) - ((FB_B1 * FB_X) >> 15)));
  }

  /* Get output samplesq */
  RUSB[0][(RvbResPos >> 1) | 0x20] = RUSB[0][RvbResPos >> 1] = (RD_RVB(MIX_DEST_A0) + RD_RVB(MIX_DEST_B0)) >> 1;
  RUSB[1][(RvbResPos >> 1) | 0x20] = RUSB[1][RvbResPos >> 1] = (RD_RVB(MIX_DEST_A1) + RD_RVB(MIX_DEST_B1)) >> 1;

  ReverbCur = (ReverbCur + 1) & 0x3FFFF;
  if(!ReverbCur)
   ReverbCur = ReverbWA;

  for(unsigned lr = 0; lr < 2; lr++)
  {
     const int16 *src = &RUSB[lr][((RvbResPos - 39) & 0x3F) >> 1];
     upsampled[lr] = src[9]; /* Reverb 2244 (Middle non-zero */
  }
 }
 else
 {
  for(unsigned lr = 0; lr < 2; lr++)
  {
     const int16 *src = &RUSB[lr][((RvbResPos - 39) & 0x3F) >> 1];
     upsampled[lr] = Reverb2244(src);
  }
 }

 RvbResPos = (RvbResPos + 1) & 0x3F;

 for(unsigned lr = 0; lr < 2; lr++)
  out[lr] = upsampled[lr];
}


INLINE void PS_SPU::RunNoise(void)
{
   const unsigned rf = ((SPUControl >> 8) & 0x3F);
   uint32 NoiseDividerInc = (2 << (rf >> 2));
   uint32 NoiseCounterInc = 4 + (rf & 0x3);

   if(rf >= 0x3C)
   {
      NoiseDividerInc = 0x8000;
      NoiseCounterInc = 8;
   }

   NoiseDivider += NoiseDividerInc;

   if(NoiseDivider & 0x8000)
   {
      NoiseDivider = 0;

      NoiseCounter += NoiseCounterInc;

      if(NoiseCounter & 0x8)
      {
         NoiseCounter &= 0x7;
         LFSR = (LFSR << 1) | (((LFSR >> 15) ^ (LFSR >> 12) ^ (LFSR >> 11) ^ (LFSR >> 10) ^ 1) & 1);
      }
   }
}

extern "C" void GetCDAudio(int32_t samples[2]);

int32 PS_SPU::UpdateFromCDC(int32 clocks)
{
   //int32 clocks = timestamp - lastts;
   int32 sample_clocks = 0;
   //lastts = timestamp;

   clock_divider -= clocks;

   while(clock_divider <= 0)
   {
      clock_divider += 768;
      sample_clocks++;
   }

   while(sample_clocks > 0)
   {
      // xxx[0] = left, xxx[1] = right

      // Accumulated sound output.
      int32 accum[2];

      // Accumulated sound output for reverb input
      int32 accum_fv[2];

      // Output of reverb processing.
      int32 reverb[2];

      // Final output.
      int32 output[2];

      accum[0]    = accum[1]    = 0;
      accum_fv[0] = accum_fv[1] = 0;
      reverb[0]   = reverb[1]   = 0;
      output[0]   = output[1]   = 0;

      const uint32 PhaseModCache = FM_Mode & ~ 1;
      /*
       **
       ** 0x1F801DAE Notes and Conjecture:
       **   -------------------------------------------------------------------------------------
       **   |   15   14 | 13 | 12 | 11 | 10  | 9  | 8 |  7 |  6  | 5    4    3    2    1    0   |
       **   |      ?    | *13| ?  | ba | *10 | wrr|rdr| df |  is |      c                       |
       **   -------------------------------------------------------------------------------------
       **
       **	c - Appears to be delayed copy of lower 6 bits from 0x1F801DAA.
       **
       **     is - Interrupt asserted out status. (apparently not instantaneous status though...)
       **
       **     df - Related to (c & 0x30) == 0x20 or (c & 0x30) == 0x30, at least.
       **          0 = DMA busy(FIFO not empty when in DMA write mode?)?
       **	    1 = DMA ready?  Something to do with the FIFO?
       **
       **     rdr - Read(DMA read?) Ready?
       **
       **     wrr - Write(DMA write?) Ready?
       **
       **     *10 - Unknown.  Some sort of (FIFO?) busy status?(BIOS tests for this bit in places)
       **
       **     ba - Alternates between 0 and 1, even when SPUControl bit15 is 0; might be related to CD audio and voice 1 and 3 writing to SPU RAM.
       **
       **     *13 - Unknown, was set to 1 when testing with an SPU delay system reg value of 0x200921E1(test result might not be reliable, re-run).
       */
      SPUStatus = SPUControl & 0x3F;
      SPUStatus |= IRQAsserted ? 0x40 : 0x00;

      if(Regs[0xD6] == 0x4)	// TODO: Investigate more(case 0x2C in global regs r/w handler)
         SPUStatus |= (CWA & 0x100) ? 0x800 : 0x000;

      for(int voice_num = 0; voice_num < 24; voice_num++)
      {
         SPU_Voice *voice = &Voices[voice_num];
         int32 voice_pvs;

         voice->PreLRSample = 0;

         //PSX_WARNING("[SPU] Voice %d CurPhase=%08x, pitch=%04x, CurAddr=%08x", voice_num, voice->CurPhase, voice->Pitch, voice->CurAddr);

         //
         // Decode new samples if necessary.
         //
         RunDecoder(voice);


         //
         //
         //
         int l, r;

         if(Noise_Mode & (1 << voice_num))
            voice_pvs = (int16)LFSR;
         else
         {
            const int si = voice->DecodeReadPos;
            const int pi = ((voice->CurPhase & 0xFFF) >> 4);

            voice_pvs = ((voice->DecodeBuffer[(si + 0) & 0x1F] * FIR_Table[pi][0]) +
                  (voice->DecodeBuffer[(si + 1) & 0x1F] * FIR_Table[pi][1]) +
                  (voice->DecodeBuffer[(si + 2) & 0x1F] * FIR_Table[pi][2]) +   
                  (voice->DecodeBuffer[(si + 3) & 0x1F] * FIR_Table[pi][3])) >> 15;
         }

         voice_pvs = (voice_pvs * (int16)voice->ADSR.EnvLevel) >> 15;
         voice->PreLRSample = voice_pvs;

         if(voice_num == 1 || voice_num == 3)
         {
            int index = voice_num >> 1;

            WriteSPURAM(0x400 | (index * 0x200) | CWA, voice_pvs);
         }


         l = (voice_pvs * voice->Sweep[0].ReadVolume()) >> 15;
         r = (voice_pvs * voice->Sweep[1].ReadVolume()) >> 15;

         accum[0] += l;
         accum[1] += r;

         if(Reverb_Mode & (1 << voice_num))
         {
            accum_fv[0] += l;
            accum_fv[1] += r;
         }

         // Run sweep
         for(int lr = 0; lr < 2; lr++)
         {
            if((voice->Sweep[lr].Control & 0x8000))
               voice->Sweep[lr].Clock();
            else
               voice->Sweep[lr].Current = (voice->Sweep[lr].Control & 0x7FFF) << 1;
         }

         // Increment stuff
         if(!voice->DecodePlayDelay)
         {
            unsigned phase_inc;

            // Run enveloping
            RunEnvelope(voice);

            if(PhaseModCache & (1 << voice_num))
            {
               // This old formula: phase_inc = (voice->Pitch * ((voice - 1)->PreLRSample + 0x8000)) >> 15;
               // is incorrect, as it does not handle carrier pitches >= 0x8000 properly.
               phase_inc = voice->Pitch + (((int16)voice->Pitch * ((voice - 1)->PreLRSample)) >> 15);
            }
            else
               phase_inc = voice->Pitch;

            if(phase_inc > 0x3FFF)
               phase_inc = 0x3FFF;

            {
               const uint32 tmp_phase = voice->CurPhase + phase_inc;
               const unsigned used = tmp_phase >> 12;

               voice->CurPhase = tmp_phase & 0xFFF;
               voice->DecodeAvail -= used;
               voice->DecodeReadPos = (voice->DecodeReadPos + used) & 0x1F;
            }
         }
         else
            voice->DecodePlayDelay--;

         if(VoiceOff & (1U << voice_num))
         {
            if(voice->ADSR.Phase != ADSR_RELEASE)
            {
               ReleaseEnvelope(voice);
            }
         }

         if(VoiceOn & (1U << voice_num))
         {
            //printf("Voice On: %u\n", voice_num);

            ResetEnvelope(voice);

            voice->DecodeFlags = 0;
            voice->DecodeWritePos = 0;
            voice->DecodeReadPos = 0;
            voice->DecodeAvail = 0;
            voice->DecodePlayDelay = 4;

            BlockEnd &= ~(1 << voice_num);

            //
            // Weight/filter previous value initialization:
            //
            voice->DecodeM2 = 0;
            voice->DecodeM1 = 0;

            voice->CurPhase = 0;
            voice->CurAddr = voice->StartAddr & ~0x7;
            voice->IgnoreSampLA = false;
         }

         if(!(SPUControl & 0x8000))
         {
            voice->ADSR.Phase = ADSR_RELEASE;
            voice->ADSR.EnvLevel = 0;
         }
      }

      VoiceOff = 0;
      VoiceOn = 0; 

      // "Mute" control doesn't seem to affect CD audio(though CD audio reverb wasn't tested...)
      // TODO: If we add sub-sample timing accuracy, see if it's checked for every channel at different times, or just once.
      if(!(SPUControl & 0x4000))
      {
         accum[0] = 0;
         accum[1] = 0;
         accum_fv[0] = 0;
         accum_fv[1] = 0;
      }

      // Get CD-DA
      {
         int32 cda_raw[2];
         int32 cdav[2];
         // const unsigned freq = (PSX_CDC->AudioBuffer.ReadPos < PSX_CDC->AudioBuffer.Size) ? PSX_CDC->AudioBuffer.Freq : 0;

         cda_raw[0] = cda_raw[1] = 0;

         // if (freq)
            GetCDAudio(cda_raw);	// PS_CDC::GetCDAudio() guarantees the variables passed by reference will be set to 0,
         // and that their range shall be -32768 through 32767.

         WriteSPURAM(CWA | 0x000, cda_raw[0]);
         WriteSPURAM(CWA | 0x200, cda_raw[1]);

         for(unsigned i = 0; i < 2; i++)
            cdav[i] = (cda_raw[i] * CDVol[i]) >> 15;

         if(SPUControl & 0x0001)
         {
            accum[0] += cdav[0];
            accum[1] += cdav[1];

            if(SPUControl & 0x0004)	// TODO: Test this bit(and see if it is really dependent on bit0)
            {
               accum_fv[0] += cdav[0];
               accum_fv[1] += cdav[1];
            }
         }
      }

      CWA = (CWA + 1) & 0x1FF;

      RunNoise();

      for (unsigned lr = 0; lr < 2; lr++)
         clamp(&accum_fv[lr], -32768, 32767);

      RunReverb(accum_fv, reverb);

      for(unsigned lr = 0; lr < 2; lr++)
      {
         accum[lr] += ((reverb[lr] * ReverbVol[lr]) >> 15);
         clamp(&accum[lr],  -32768, 32767);
         output[lr] = (accum[lr] * GlobalSweep[lr].ReadVolume()) >> 15;
         clamp(&output[lr], -32768, 32767);
      }

      if(IntermediateBufferPos < 4096)	// Overflow might occur in some debugger use cases.
      {
         // 75%, for some (resampling) headroom.
         for(unsigned lr = 0; lr < 2; lr++)
            IntermediateBuffer[IntermediateBufferPos][lr] = (output[lr] * 3 + 2) >> 2;

         IntermediateBufferPos++;
      }

      sample_clocks--;

      // Clock global sweep
      for(unsigned lr = 0; lr < 2; lr++)
      {
         if((GlobalSweep[lr].Control & 0x8000))
            GlobalSweep[lr].Clock();
         else
            GlobalSweep[lr].Current = (GlobalSweep[lr].Control & 0x7FFF) << 1;
      }
   }

   //assert(clock_divider < 768);

   return clock_divider;
}
#include <stdio.h>
void PS_SPU::WriteDMA(uint32 V)
{
   //SPUIRQ_DBG("DMA Write, RWAddr after=0x%06x", RWAddr);
   WriteSPURAM(RWAddr, V);
   RWAddr = (RWAddr + 1) & 0x3FFFF;

   WriteSPURAM(RWAddr, V >> 16);
   RWAddr = (RWAddr + 1) & 0x3FFFF;


   CheckIRQAddr(RWAddr);
}

uint32 PS_SPU::ReadDMA(void)
{
   uint32 ret = (uint16)ReadSPURAM(RWAddr);
   RWAddr = (RWAddr + 1) & 0x3FFFF;

   ret |= (uint32)(uint16)ReadSPURAM(RWAddr) << 16;
   RWAddr = (RWAddr + 1) & 0x3FFFF;

   CheckIRQAddr(RWAddr);

   //SPUIRQ_DBG("DMA Read, RWAddr after=0x%06x", RWAddr);

   return(ret);
}

void PS_SPU::Write(int32_t timestamp, uint32 A, uint16 V, char* file, int line)
{
   // writes.push_back({A, V, std::string(file), line});
   // if((A & 0x3FF)) //  < 0x180
   // printf("[SPU] Write: %08x %04x\n", A, V);

   A &= 0x3FF;

   if(A >= 0x200)
   {
      // printf("Write: %08x %04x\n", A, V);
      if(A < 0x260)
      {
         SPU_Voice *voice = &Voices[(A - 0x200) >> 2];
         voice->Sweep[(A & 2) >> 1].WriteVolume(V);
      }
      else if(A < 0x280)
         AuxRegs[(A & 0x1F) >> 1] = V;

      return;
   }

   if(A < 0x180)
   {
      SPU_Voice *voice = &Voices[A >> 4];

      switch(A & 0xF)
      {
         case 0x00:
         case 0x02:
            voice->Sweep[(A & 2) >> 1].WriteControl(V);
            break;
         case 0x04:
            voice->Pitch = V;
            break;
         case 0x06:
            voice->StartAddr = (V << 2) & 0x3FFFF;
            break;
         case 0x08:
            voice->ADSRControl &= 0xFFFF0000;
            voice->ADSRControl |= V;
            CacheEnvelope(voice);
            break;
         case 0x0A:
            voice->ADSRControl &= 0x0000FFFF;
            voice->ADSRControl |= V << 16;
            CacheEnvelope(voice);
            break;
         case 0x0C:
            voice->ADSR.EnvLevel = V;
            break;
         case 0x0E:
            voice->LoopAddr = (V << 2) & 0x3FFFF;
            voice->IgnoreSampLA = true;
#if 0
            if((voice - Voices) == 22)
            {
               SPUIRQ_DBG("Manual loop address setting for voice %d: %04x", (int)(voice - Voices), V);
            }
#endif
            break;
      }
   }
   else
   {
      switch(A & 0x7F)
      {
         case 0x00:
         case 0x02: GlobalSweep[(A & 2) >> 1].WriteControl(V);
                    break;

         case 0x04: ReverbVol[0] = (int16)V;
                    break;

         case 0x06: ReverbVol[1] = (int16)V;
                    break;

                    // Voice ON:
         case 0x08: VoiceOn &= 0xFFFF0000;
                    VoiceOn |= V << 0;
                    break;

         case 0x0a: VoiceOn &= 0x0000FFFF;
                    VoiceOn |= (V & 0xFF) << 16;
                    break;

                    // Voice OFF:
         case 0x0c: VoiceOff &= 0xFFFF0000;
                    VoiceOff |= V << 0;
                    break;

         case 0x0e: VoiceOff &= 0x0000FFFF;
                    VoiceOff |= (V & 0xFF) << 16;
                    break;

         case 0x10: FM_Mode &= 0xFFFF0000;
                    FM_Mode |= V << 0;
                    break;

         case 0x12: FM_Mode &= 0x0000FFFF;
                    FM_Mode |= (V & 0xFF) << 16;
                    break;

         case 0x14: Noise_Mode &= 0xFFFF0000;
                    Noise_Mode |= V << 0;
                    break;

         case 0x16: Noise_Mode &= 0x0000FFFF;
                    Noise_Mode |= (V & 0xFF) << 16;
                    break;

         case 0x18: Reverb_Mode &= 0xFFFF0000;
                    Reverb_Mode |= V << 0;
                    break;

         case 0x1A: Reverb_Mode &= 0x0000FFFF;
                    Reverb_Mode |= (V & 0xFF) << 16;
                    break;

         case 0x1C: BlockEnd &= 0xFFFF0000;
                    BlockEnd |= V << 0;
                    break;

         case 0x1E: BlockEnd &= 0x0000FFFF;
                    BlockEnd |= V << 16;
                    break;

         case 0x22: ReverbWA = (V << 2) & 0x3FFFF;
                    ReverbCur = ReverbWA;
                    //PSX_WARNING("[SPU] Reverb WA set: 0x%04x", V);
                    break;

         case 0x24:
                    IRQAddr = (V << 2) & 0x3FFFF;
                    CheckIRQAddr(RWAddr);
                    //SPUIRQ_DBG("Set IRQAddr=0x%06x", IRQAddr);
                    break;

         case 0x26:
                    RWAddr = (V << 2) & 0x3FFFF;	      
                    CheckIRQAddr(RWAddr);
                    //SPUIRQ_DBG("Set RWAddr=0x%06x", RWAddr);
                    break;

         case 0x28: WriteSPURAM(RWAddr, V);
                    RWAddr = (RWAddr + 1) & 0x3FFFF;
                    CheckIRQAddr(RWAddr);
                    break;

         case 0x2A: //if((SPUControl & 0x80) && !(V & 0x80))
                    // printf("\n\n\n\n ************** REVERB PROCESSING DISABLED\n\n\n\n");

                    SPUControl = V;
                    //SPUIRQ_DBG("Set SPUControl=0x%04x -- IRQA=%06x, RWA=%06x", V, IRQAddr, RWAddr);
                    //printf("SPU control write: %04x\n", V);
                    if(!(V & 0x40))
                    {
                       IRQAsserted = false;
                       IRQ_Assert(IRQ_SPU, IRQAsserted);
                    }
                    CheckIRQAddr(RWAddr);
                    break;

         case 0x2C: 
                    //PSX_WARNING("[SPU] Global reg 0x2c set: 0x%04x", V);
                    break;

         case 0x30: CDVol[0] = (int16_t)V;
                    break;

         case 0x32: CDVol[1] = (int16_t)V;
                    break;

         case 0x34: ExternVol[0] = (int16_t)V;
                    break;

         case 0x36: ExternVol[1] = (int16_t)V;
                    break;

         case 0x38:
         case 0x3A: GlobalSweep[(A & 2) >> 1].WriteVolume(V);
                    break;
      }
   }

   Regs[(A & 0x1FF) >> 1] = V;
}

uint16 PS_SPU::Read(int32_t timestamp, uint32 A)
{
   A &= 0x3FF;

   // PSX_DBGINFO("[SPU] Read: %08x", A);

   if(A >= 0x200)
   {
      if(A < 0x260)
      {
         SPU_Voice *voice = &Voices[(A - 0x200) >> 2];

         //printf("Read: %08x %04x\n", A, voice->Sweep[(A & 2) >> 1].ReadVolume());

         return voice->Sweep[(A & 2) >> 1].ReadVolume();
      }
      else if(A < 0x280)
         return(AuxRegs[(A & 0x1F) >> 1]);

      return(0xFFFF);
   }


   if(A < 0x180)
   {
      SPU_Voice *voice = &Voices[A >> 4];

      switch(A & 0xF)
      {
         case 0x0C:
            return(voice->ADSR.EnvLevel);
         case 0x0E:
            return(voice->LoopAddr >> 2);
      }
   }
   else
   {
      switch(A & 0x7F)
      {
         case 0x1C:
            return(BlockEnd);
         case 0x1E:
            return(BlockEnd >> 16);
         case 0x26:
            //PSX_WARNING("[SPU] RWADDR Read");
            break;
         case 0x28:
            //PSX_WARNING("[SPU] SPURAM Read port(?) Read");
            {
               uint16 ret = ReadSPURAM(RWAddr);

               RWAddr = (RWAddr + 1) & 0x3FFFF;
               CheckIRQAddr(RWAddr);

               return (ret);
            }

         case 0x2a:
            return(SPUControl);

            /* FIXME: What is this used for? */
         case 0x3C:
            //PSX_WARNING("[SPU] Read Unknown: %08x", A);
            return(0);
         case 0x38:
         case 0x3A:
            return(GlobalSweep[(A & 2) >> 1].ReadVolume());
      }
   }

   return(Regs[(A & 0x1FF) >> 1]);
}

/* Save state of SPU disabled
int PS_SPU::StateAction(StateMem *sm, int load, int data_only)
{
   SFORMAT StateRegs[] =
   {
#define SFSWEEP(r) SFVAR((r).Control),	\
      SFVAR((r).Current),	\
      SFVAR((r).Divider)

#define SFVOICE(n) SFARRAY16(&Voices[n].DecodeBuffer[0], sizeof(Voices[n].DecodeBuffer) / sizeof(Voices[n].DecodeBuffer[0])),	\
      SFVAR(Voices[n].DecodeM2),											\
      SFVAR(Voices[n].DecodeM1),											\
      SFVAR(Voices[n].DecodePlayDelay),										\
      SFVAR(Voices[n].DecodeWritePos),										\
      SFVAR(Voices[n].DecodeReadPos),										\
      SFVAR(Voices[n].DecodeAvail),										\
      SFVAR(Voices[n].DecodeShift),										\
      SFVAR(Voices[n].DecodeWeight),										\
      SFVAR(Voices[n].DecodeFlags),										\
      SFVAR(Voices[n].IgnoreSampLA),										\
      \
      SFSWEEP(Voices[n].Sweep[0]),											\
      SFSWEEP(Voices[n].Sweep[1]),											\
      \
      SFVAR(Voices[n].Pitch),											\
      SFVAR(Voices[n].CurPhase),											\
      \
      SFVAR(Voices[n].StartAddr),											\
      SFVAR(Voices[n].CurAddr),											\
      SFVAR(Voices[n].ADSRControl),										\
      SFVAR(Voices[n].LoopAddr),											\
      SFVAR(Voices[n].PreLRSample),										\
      \
      SFVAR(Voices[n].ADSR.EnvLevel),										\
      SFVAR(Voices[n].ADSR.Divider),										\
      SFVAR(Voices[n].ADSR.Phase),											\
      \
      SFVAR(Voices[n].ADSR.AttackExp),										\
      SFVAR(Voices[n].ADSR.SustainExp),										\
      SFVAR(Voices[n].ADSR.SustainDec),										\
      SFVAR(Voices[n].ADSR.ReleaseExp),										\
      \
      SFVAR(Voices[n].ADSR.AttackRate),										\
      SFVAR(Voices[n].ADSR.DecayRate),										\
      SFVAR(Voices[n].ADSR.SustainRate),										\
      SFVAR(Voices[n].ADSR.ReleaseRate),										\
      \
      SFVAR(Voices[n].ADSR.SustainLevel)

      SFVOICE(0),
      SFVOICE(1),
      SFVOICE(2),
      SFVOICE(3),
      SFVOICE(4),
      SFVOICE(5),
      SFVOICE(6),
      SFVOICE(7),
      SFVOICE(8),
      SFVOICE(9),
      SFVOICE(10),
      SFVOICE(11),
      SFVOICE(12),
      SFVOICE(13),
      SFVOICE(14),
      SFVOICE(15),
      SFVOICE(16),
      SFVOICE(17),
      SFVOICE(18),
      SFVOICE(19),
      SFVOICE(20),
      SFVOICE(21),
      SFVOICE(22),
      SFVOICE(23),
#undef SFVOICE

      SFVAR(NoiseDivider),
      SFVAR(NoiseCounter),
      SFVAR(LFSR),

      SFVAR(FM_Mode),
      SFVAR(Noise_Mode),
      SFVAR(Reverb_Mode),

      SFVAR(ReverbWA),

      SFSWEEP(GlobalSweep[0]),
      SFSWEEP(GlobalSweep[1]),

      SFARRAY32(ReverbVol, sizeof(ReverbVol) / sizeof(ReverbVol[0])),

      SFARRAY32(CDVol, sizeof(CDVol) / sizeof(CDVol[0])),
      SFARRAY32(ExternVol, sizeof(ExternVol) / sizeof(ExternVol[0])),

      SFVAR(IRQAddr),

      SFVAR(RWAddr),

      SFVAR(SPUControl),

      SFVAR(VoiceOn),
      SFVAR(VoiceOff),

      SFVAR(BlockEnd),

      SFVAR(CWA),

      SFARRAY16(Regs, sizeof(Regs) / sizeof(Regs[0])),
      SFARRAY16(AuxRegs, sizeof(AuxRegs) / sizeof(AuxRegs[0])),

      SFARRAY16(&RDSB[0][0], sizeof(RDSB) / sizeof(RDSB[0][0])),
      SFVAR(RvbResPos),

      SFARRAY16(&RUSB[0][0], sizeof(RUSB) / sizeof(RUSB[0][0])),

      SFVAR(ReverbCur),
      SFVAR(IRQAsserted),

      SFVAR(clock_divider),

      SFARRAY16(SPURAM, 524288 / sizeof(uint16)),
      SFEND
   };
#undef SFSWEEP
   int ret = 1;

   ret &= MDFNSS_StateAction(sm, load, data_only, StateRegs, "SPU");

   if(load)
   {
      for(unsigned i = 0; i < 24; i++)
      {
         Voices[i].DecodeReadPos &= 0x1F;
         Voices[i].DecodeWritePos &= 0x1F;
         Voices[i].CurAddr &= 0x3FFFF;
         Voices[i].StartAddr &= 0x3FFFF;
         Voices[i].LoopAddr &= 0x3FFFF;
      }

      if(clock_divider <= 0 || clock_divider > 768)
         clock_divider = 768;

      RWAddr &= 0x3FFFF;
      CWA &= 0x1FF;

      ReverbWA &= 0x3FFFF;
      ReverbCur &= 0x3FFFF;

      RvbResPos &= 0x3F;

      IRQ_Assert(IRQ_SPU, IRQAsserted);
   }

   return(ret);
}
*/

uint16 PS_SPU::PeekSPURAM(uint32 address)
{
   return(SPURAM[address & 0x3FFFF]);
}

void PS_SPU::PokeSPURAM(uint32 address, uint16 value)
{
   SPURAM[address & 0x3FFFF] = value;
}

uint32 PS_SPU::GetRegister(unsigned int which, char *special, const uint32 special_len)
{
   if(which >= 0x8000)
   {
      unsigned int v = (which - 0x8000) >> 8;

      switch((which & 0xFF) | 0x8000)
      {
         case GSREG_V0_VOL_CTRL_L:
            return Regs[v * 8 + 0x0];
         case GSREG_V0_VOL_CTRL_R:
            return Regs[v * 8 + 0x1];
         case GSREG_V0_VOL_L:
            return Voices[v].Sweep[0].ReadVolume() & 0xFFFF;
         case GSREG_V0_VOL_R:
            return Voices[v].Sweep[1].ReadVolume() & 0xFFFF;
         case GSREG_V0_PITCH:
            return Voices[v].Pitch;
         case GSREG_V0_STARTADDR:
            return Voices[v].StartAddr;
         case GSREG_V0_ADSR_CTRL:
            return Voices[v].ADSRControl;
         case GSREG_V0_ADSR_LEVEL:
            return Voices[v].ADSR.EnvLevel;
         case GSREG_V0_LOOP_ADDR:
            return Voices[v].LoopAddr;
         case GSREG_V0_READ_ADDR:
            return Voices[v].CurAddr;
      }
   }
   else if (which >= 18 && which <= 49)
      return ReverbRegs[which - GSREG_FB_SRC_A];
   else switch(which)
   {
      case GSREG_SPUCONTROL:
         return SPUControl;
      case GSREG_FM_ON:
         return FM_Mode;
      case GSREG_NOISE_ON:
         return Noise_Mode;
      case GSREG_REVERB_ON:
         return Reverb_Mode;
      case GSREG_CDVOL_L:
         return (uint16)CDVol[0];
      case GSREG_CDVOL_R:
         return (uint16)CDVol[1];
      case GSREG_MAINVOL_CTRL_L:
         return Regs[0xC0];
      case GSREG_MAINVOL_CTRL_R:
         return Regs[0xC1];
      case GSREG_MAINVOL_L:
         return GlobalSweep[0].ReadVolume() & 0xFFFF;
      case GSREG_MAINVOL_R:
         return GlobalSweep[1].ReadVolume() & 0xFFFF;
      case GSREG_RVBVOL_L:
         return (uint16)ReverbVol[0];
      case GSREG_RVBVOL_R:
         return (uint16)ReverbVol[1];
      case GSREG_RWADDR:
         return RWAddr;
      case GSREG_IRQADDR:
         return IRQAddr;
      case GSREG_REVERBWA:
         return ReverbWA >> 2;
      case GSREG_VOICEON:
         return VoiceOn;
      case GSREG_VOICEOFF:
         return VoiceOff;
      case GSREG_BLOCKEND:
         return BlockEnd;
   }

   return 0xDEADBEEF;
}

void PS_SPU::SetRegister(unsigned int which, uint32 value)
{
   if(which >= GSREG_FB_SRC_A && which <= GSREG_IN_COEF_R)
      ReverbRegs[which - GSREG_FB_SRC_A] = value;
   else switch(which)
   {
      case GSREG_SPUCONTROL:
         SPUControl = value;
         break;

      case GSREG_FM_ON:
         FM_Mode = value & 0xFFFFFF;
         break;

      case GSREG_NOISE_ON:
         Noise_Mode = value & 0xFFFFFF;
         break;

      case GSREG_REVERB_ON:
         Reverb_Mode = value & 0xFFFFFF;
         break;

      case GSREG_CDVOL_L:
         CDVol[0] = (int16)value;
         break;

      case GSREG_CDVOL_R:
         CDVol[1] = (int16)value;
         break;

      case GSREG_MAINVOL_CTRL_L:
         Regs[0xC0] = value;
         GlobalSweep[0].WriteControl(value);
         //GlobalSweep[0].Control = value;
         break;

      case GSREG_MAINVOL_CTRL_R:
         Regs[0xC1] = value;
         GlobalSweep[1].WriteControl(value);
         //GlobalSweep[1].Control = value;
         break;

      case GSREG_MAINVOL_L:
         GlobalSweep[0].WriteVolume(value);
         break;

      case GSREG_MAINVOL_R:
         GlobalSweep[1].WriteVolume(value);
         break;

      case GSREG_RVBVOL_L:
         ReverbVol[0] = (int16)value;
         break;

      case GSREG_RVBVOL_R:
         ReverbVol[1] = (int16)value;
         break;

      case GSREG_RWADDR:
         RWAddr = value & 0x3FFFF;
         break;

      case GSREG_IRQADDR:
         IRQAddr = value & 0x3FFFC;
         break;

         //
         // REVERB_WA
         //

      case GSREG_VOICEON:
         VoiceOn = value & 0xFFFFFF;
         break;

      case GSREG_VOICEOFF:
         VoiceOff = value & 0xFFFFFF;
         break;

      case GSREG_BLOCKEND:
         BlockEnd = value & 0xFFFFFF;
         break;
   }
}