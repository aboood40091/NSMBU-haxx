void setPlayerJumpArc(float jumpArc) {
    #ifdef REGION_NSMBU_EU_Latest
    float *PlayerJumpArcPtr = (float *)0x1066CA20;
    #else
    float *PlayerJumpArcPtr = (float *)0x1066CA00;
    #endif // REGION_NSMBU_EU_Latest

    *PlayerJumpArcPtr = jumpArc;
}

void setMiniPlayerJumpArc(float jumpArc) {
    #ifdef REGION_NSMBU_EU_Latest
    float *MiniPlayerJumpArcPtr = (float *)0x1066CA68;
    #else
    float *MiniPlayerJumpArcPtr = (float *)0x1066CA48;
    #endif // REGION_NSMBU_EU_Latest

    *MiniPlayerJumpArcPtr = jumpArc;
}

void setPlayerJumpMax(float jumpMax) {
    #ifdef REGION_NSMBU_EU_Latest
    float *PlayerJumpMaxPtr = (float *)0x10669088;
    #else
    float *PlayerJumpMaxPtr = (float *)0x10669068;
    #endif // REGION_NSMBU_EU_Latest

    *PlayerJumpMaxPtr = jumpMax;
}

void setPlayerDescentRate(float descentRate) {
    #ifdef REGION_NSMBU_EU_Latest
    float *PlayerDescentRatePtr = (float *)0x10669094;
    #else
    float *PlayerDescentRatePtr = (float *)0x10669074;
    #endif // REGION_NSMBU_EU_Latest

    *PlayerDescentRatePtr = descentRate;
}
