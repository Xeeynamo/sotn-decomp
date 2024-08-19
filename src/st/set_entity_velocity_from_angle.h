void SetEntityVelocityFromAngle(s32 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = GetSineScaled(arg0, arg1);
    g_CurrentEntity->velocityY = GetSineScaled(arg0 - 0x40, arg1);
}
