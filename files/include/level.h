#pragma once

struct LevelArea {
    char _0[4];
    void *blockPtrs[15];
    // ...
};

struct LevelData {
    char _0[0x10];
    LevelArea areas[4];
};

struct AreaSettings {
	char _0[8];
	unsigned short flags;
	// ...
};

struct LevelInfoStruct {
    char _0[0x12];
    char currentAreaId;
    // ...
};

#ifdef __cplusplus
extern "C" {
#endif

LevelArea *getAreaById(LevelData *_this, unsigned int id);

#ifdef __cplusplus
}
#endif
