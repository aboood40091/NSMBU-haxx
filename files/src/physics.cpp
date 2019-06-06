void setPlayerJumpArc(float jumpArc) {
    #ifdef Cemu

    #ifdef REGION_NSMBU_EU_Latest_Cemu
    float *PlayerJumpArcPtr = (float *)0x1016a820;
    #else
    float *PlayerJumpArcPtr = (float *)0x1016a800;
    #endif // REGION_NSMBU_EU_Latest

    #else

    #ifdef REGION_NSMBU_EU_Latest
    float *PlayerJumpArcPtr = (float *)0x1066CA20;
    #else
    float *PlayerJumpArcPtr = (float *)0x1066CA00;
    #endif // REGION_NSMBU_EU_Latest

    #endif // Cemu

    *PlayerJumpArcPtr = jumpArc;
}

void setMiniPlayerJumpArc(float jumpArc) {
    #ifdef Cemu

    #ifdef REGION_NSMBU_EU_Latest_Cemu
    float *MiniPlayerJumpArcPtr = (float *)0x1016a868;
    #else
    float *MiniPlayerJumpArcPtr = (float *)0x1016a848;
    #endif // REGION_NSMBU_EU_Latest

    #else

    #ifdef REGION_NSMBU_EU_Latest
    float *MiniPlayerJumpArcPtr = (float *)0x1066CA68;
    #else
    float *MiniPlayerJumpArcPtr = (float *)0x1066CA48;
    #endif // REGION_NSMBU_EU_Latest

    #endif // Cemu

    *MiniPlayerJumpArcPtr = jumpArc;
}

void setPlayerJumpMax(float jumpMax) {
    #ifdef Cemu

    #ifdef REGION_NSMBU_EU_Latest_Cemu
    float *PlayerJumpMaxPtr = (float *)0x10166e88;
    #else
    float *PlayerJumpMaxPtr = (float *)0x10166e68;
    #endif // REGION_NSMBU_EU_Latest

    #else

    #ifdef REGION_NSMBU_EU_Latest
    float *PlayerJumpMaxPtr = (float *)0x10669088;
    #else
    float *PlayerJumpMaxPtr = (float *)0x10669068;
    #endif // REGION_NSMBU_EU_Latest

    #endif // Cemu

    *PlayerJumpMaxPtr = jumpMax;
}

void setPlayerDescentRate(float descentRate) {
    #ifdef Cemu

    #ifdef REGION_NSMBU_EU_Latest_Cemu
    float *PlayerDescentRatePtr = (float *)0x10166e94;
    #else
    float *PlayerDescentRatePtr = (float *)0x10166e74;
    #endif // REGION_NSMBU_EU_Latest

    #else

    #ifdef REGION_NSMBU_EU_Latest
    float *PlayerDescentRatePtr = (float *)0x10669094;
    #else
    float *PlayerDescentRatePtr = (float *)0x10669074;
    #endif // REGION_NSMBU_EU_Latest

    #endif // Cemu

    *PlayerDescentRatePtr = descentRate;
}
