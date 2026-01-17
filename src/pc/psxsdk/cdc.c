/******************************************************************************/
/* Mednafen Sony PS1 Emulation Module                                         */
/******************************************************************************/
/* cdc.cpp:
**  Copyright (C) 2011-2021 Mednafen Team
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <common.h>
#include <inttypes.h>
#include <string.h>
#include "cdc.h"

//
// output should be readable at -2 and -1
static void DecodeXAADPCM(const uint8_t* input, int16_t* output,
                          const unsigned shift, const unsigned weight) {
    // Weights copied over from SPU channel ADPCM playback code, may not be
    // entirely the same for CD-XA ADPCM, we need to run tests.
    static const int32_t Weights[16][2] = {
        // s-1    s-2
        {0, 0}, {60, 0}, {115, -52}, {98, -55}, {122, -60},
    };

    for (int i = 0; i < 28; i++) {
        int32_t sample;

        sample = (int16_t)(input[i] << 8);
        sample >>= shift;

        sample += ((output[i - 1] * Weights[weight][0]) >> 6) +
                  ((output[i - 2] * Weights[weight][1]) >> 6);

        if (sample < -32768)
            sample = -32768;

        if (sample > 32767)
            sample = 32767;

        output[i] = sample;
    }
}

struct XA_Subheader {
    uint8_t file;
    uint8_t channel;
    uint8_t submode;
    uint8_t coding;

    uint8_t file_dup;
    uint8_t channel_dup;
    uint8_t submode_dup;
    uint8_t coding_dup;
};

struct XA_SoundGroup {
    uint8_t params[16];
    uint8_t samples[112];
};

#define XA_CODING_8BIT 0x10
#define XA_CODING_189 0x04
#define XA_CODING_STEREO 0x01

int16_t xa_previous[2][2];

int current_file = 0;
int current_channel = 0;

void XA_ProcessSector(const uint8_t* sdata, struct CD_Audio_Buffer* ab) {
    const struct XA_Subheader* sh = (const struct XA_Subheader*)&sdata[12 + 4];
    const unsigned unit_index_shift = (sh->coding & XA_CODING_8BIT) ? 0 : 1;

    // xa is interleaved so skip if the file and channel don't match
    if (sh->file != current_file || sh->channel != current_channel) {
        return;
    }

    // printf("File: 0x%02x 0x%02x - Channel: 0x%02x 0x%02x - Submode: 0x%02x
    // 0x%02x - Coding: 0x%02x 0x%02x - \n", sh->file, sh->file_dup,
    // sh->channel, sh->channel_dup, sh->submode, sh->submode_dup, sh->coding,
    // sh->coding_dup);
    ab->ReadPos = 0;
    ab->Size = 18 * (4 << unit_index_shift) * 28;

    if (sh->coding & XA_CODING_STEREO)
        ab->Size >>= 1;

    ab->Freq = (sh->coding & XA_CODING_189) ? 3 : 6;

    // fprintf(stderr, "Coding: %02x %02x\n", sh->coding, sh->coding_dup);

    for (unsigned group = 0; group < 18; group++) {
        const struct XA_SoundGroup* sg =
            (const struct XA_SoundGroup*)&sdata[12 + 4 + 8 + group * 128];

        for (unsigned unit = 0; unit < (4U << unit_index_shift); unit++) {
            const uint8_t param = sg->params[(unit & 3) | ((unit & 4) << 1)];
            const uint8_t param_copy =
                sg->params[4 | (unit & 3) | ((unit & 4) << 1)];
            uint8_t ibuffer[28];
            int16_t obuffer[2 + 28];

            if (param != param_copy) {
                // PSX_WARNING(
                //     "[CDC] CD-XA param != param_copy --- %d %02x %02x\n",
                //     unit, param, param_copy);
            }

            for (unsigned i = 0; i < 28; i++) {
                uint8_t tmp = sg->samples[i * 4 + (unit >> unit_index_shift)];

                if (unit_index_shift) {
                    tmp <<= (unit & 1) ? 0 : 4;
                    tmp &= 0xf0;
                }

                ibuffer[i] = tmp;
            }

            const bool ocn =
                (bool)(unit & 1) && (sh->coding & XA_CODING_STEREO);

            obuffer[0] = xa_previous[ocn][0];
            obuffer[1] = xa_previous[ocn][1];

            DecodeXAADPCM(ibuffer, &obuffer[2], param & 0x0F, param >> 4);

            xa_previous[ocn][0] = obuffer[28];
            xa_previous[ocn][1] = obuffer[29];

            if (param != param_copy)
                memset(obuffer, 0, sizeof(obuffer));

            if (sh->coding & XA_CODING_STEREO) {
                for (unsigned s = 0; s < 28; s++) {
                    ab->Samples[ocn][group * (2 << unit_index_shift) * 28 +
                                     (unit >> 1) * 28 + s] = obuffer[2 + s];
                }
            } else {
                for (unsigned s = 0; s < 28; s++) {
                    ab->Samples[0][group * (4 << unit_index_shift) * 28 +
                                   unit * 28 + s] = obuffer[2 + s];
                    ab->Samples[1][group * (4 << unit_index_shift) * 28 +
                                   unit * 28 + s] = obuffer[2 + s];
                }
            }
        }
    }

#if 0
 // Test
 for(unsigned i = 0; i < ab->Size; i++)
 {
  static unsigned counter = 0;

  ab->Samples[0][i] = (counter & 2) ? -0x6000 : 0x6000;
  ab->Samples[1][i] = rand();
  counter++;
 }
#endif
}

struct CD_Audio_Buffer AudioBuffer;

static const int16_t CDADPCMImpulse[7][25] = {
    {
        0,    -5,    17,    -35,   70,    -23,  -68,   347, -839,
        2062, -4681, 15367, 21472, -5882, 2810, -1352, 635, -235,
        26,   43,    -35,   16,    -8,    2,    0,
    }, /* 0 */
    {
        0,    -2,    10,   -34,   65,    -84,  52,    9,   -266,
        1024, -2680, 9036, 26516, -6016, 3021, -1571, 848, -365,
        107,  10,    -16,  17,    -8,    3,    -1,
    }, /* 1 */
    {
        -2,  0,    3,    -19,   60,    -75,  162,   -227, 306,
        -67, -615, 3229, 29883, -4532, 2488, -1471, 882,  -424,
        166, -27,  5,    6,     -8,    3,    -1,
    }, /* 2 */
    {
        -1,   3,    -2,    -5,    31,    -74,  179,  -402, 689,
        -926, 1272, -1446, 31033, -1446, 1272, -926, 689,  -402,
        179,  -74,  31,    -5,    -2,    3,    -1,
    }, /* 3 */
    {
        -1,    3,    -8,    6,     5,    -27,  166, -424, 882,
        -1471, 2488, -4532, 29883, 3229, -615, -67, 306,  -227,
        162,   -75,  60,    -19,   3,    0,    -2,
    }, /* 4 */
    {
        -1,    3,    -8,    17,    -16,  10,    107,  -365, 848,
        -1571, 3021, -6016, 26516, 9036, -2680, 1024, -266, 9,
        52,    -84,  65,    -34,   10,   -2,    0,
    }, /* 5 */
    {
        0,     2,    -8,    16,    -35,   43,    26,   -235, 635,
        -1352, 2810, -5882, 21472, 15367, -4681, 2062, -839, 347,
        -68,   -23,  70,    -35,   17,    -5,    0,
    }, /* 6 */
};

void ReadAudioBuffer(int32_t samples[2]) {
    samples[0] = AudioBuffer.Samples[0][AudioBuffer.ReadPos];
    samples[1] = AudioBuffer.Samples[1][AudioBuffer.ReadPos];

    AudioBuffer.ReadPos++;
}

void clamp(int32_t* val, int32_t minimum, int32_t maximum) {
    if (*val < minimum) {
        *val = minimum;
    }
    if (*val > maximum) {
        *val = maximum;
    }
}

int16_t ADPCM_ResampBuf[2][32 * 2];
uint8_t ADPCM_ResampCurPos;
uint8_t ADPCM_ResampCurPhase;
uint8_t DecodeVolume[2][2];
int Muted = 0;

void ApplyVolume(int32_t samples[2]) {

    DecodeVolume[0][0] = 0x80;
    DecodeVolume[0][1] = 0x00;
    DecodeVolume[1][0] = 0x00;
    DecodeVolume[1][1] = 0x80;
    //
    // Take care not to alter samples[] before we're done calculating the new
    // output samples!
    //
    int32_t left_out = ((samples[0] * DecodeVolume[0][0]) >> 7) +
                       ((samples[1] * DecodeVolume[1][0]) >> 7);
    int32_t right_out = ((samples[0] * DecodeVolume[0][1]) >> 7) +
                        ((samples[1] * DecodeVolume[1][1]) >> 7);

    clamp(&left_out, -32768, 32767);
    clamp(&right_out, -32768, 32767);

    if (Muted) {
        left_out = 0;
        right_out = 0;
    }

    samples[0] = left_out;
    samples[1] = right_out;
}

//
// This function must always set samples[0] and samples[1], even if just to 0;
// range of samples[n] shall be restricted to -32768 through 32767.
//
void GetCDAudio(int32_t samples[2]) {
    const unsigned freq =
        (AudioBuffer.ReadPos < AudioBuffer.Size) ? AudioBuffer.Freq : 0;

    // if(AudioBuffer.ReadPos  % 10  == 0)
    // printf("AudioBuffer.ReadPos  %d\n", AudioBuffer.ReadPos );

    samples[0] = 0;
    samples[1] = 0;

    if (!freq)
        return;

    if (freq == 7 || freq == 14) {
        ReadAudioBuffer(samples);
        if (freq == 14)
            ReadAudioBuffer(samples);
    } else {
        int32_t out_tmp[2] = {0, 0};

        for (unsigned i = 0; i < 2; i++) {
            const int16_t* imp = CDADPCMImpulse[ADPCM_ResampCurPhase];
            int16_t* wf =
                &ADPCM_ResampBuf[i][(ADPCM_ResampCurPos + 32 - 25) & 0x1F];

            for (unsigned s = 0; s < 25; s++) {
                out_tmp[i] += imp[s] * wf[s];
            }

            out_tmp[i] >>= 15;
            clamp(&out_tmp[i], -32768, 32767);
            samples[i] = out_tmp[i];
        }

        ADPCM_ResampCurPhase += freq;

        if (ADPCM_ResampCurPhase >= 7) {
            int32_t raw[2] = {0, 0};

            ADPCM_ResampCurPhase -= 7;
            ReadAudioBuffer(raw);

            for (unsigned i = 0; i < 2; i++) {
                ADPCM_ResampBuf[i][ADPCM_ResampCurPos + 0] =
                    ADPCM_ResampBuf[i][ADPCM_ResampCurPos + 32] = raw[i];
            }
            ADPCM_ResampCurPos = (ADPCM_ResampCurPos + 1) & 0x1F;
        }
    }

    //
    // Algorithmically, volume is applied after resampling for CD-XA ADPCM
    // playback, per PS1 tests(though when "mute" is applied wasn't tested).
    //
    ApplyVolume(samples);
}
