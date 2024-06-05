extern u16 unk15_rot[];
extern u32 unk15_yVel[];

// looks like a particle of dust fading away
void EntityUnkId15(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->flags = FLAG_UNK_2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        arg0->palette = PAL_OVL(0x195);
        arg0->animSet = ANIMSET_DRA(5);
        arg0->animCurFrame = 1;
        arg0->drawMode = DRAW_TPAGE;
        arg0->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        arg0->rotY = arg0->rotX = unk15_rot[arg0->params];
        arg0->velocityY = unk15_yVel[arg0->params];
        arg0->step++;
    } else {
        arg0->animFrameDuration++;
        arg0->posY.val -= arg0->velocityY;
        if (!(arg0->animFrameDuration & 1)) {
            arg0->animCurFrame++;
        }
        if (arg0->animFrameDuration > 36) {
            DestroyEntity(arg0);
        }
    }
}
