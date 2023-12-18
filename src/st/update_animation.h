s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            *(s16*)&prim->u0 = tempUv;
            *(s16*)&prim->u1 = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            *(s16*)&prim->u3 = tempUv + sp0;
            ++prim->p1;
            *(s16*)&prim->u2 = tempUv + (new_var << 8);
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            *(s16*)&prim->u0 = tempUv;
            *(s16*)&prim->u1 = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            *(s16*)&prim->u3 = tempUv + sp0;
            ++prim->p1;
            *(s16*)&prim->u2 = tempUv + (new_var2 << 8);
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}