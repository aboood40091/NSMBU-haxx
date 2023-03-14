#pragma once

#include <heap/seadDisposer.h>

#include "util/rect.h"

struct Options
{
    // Official name not known, but is called area options by the modding community.

    u32 def_events[2];  // Not u64
    u16 loop;
    u16 time_0;
    u8  _unused0[4];
    u8  start_next_goto;
    u8  _unused1[2];
    u8  start_next_goto_coin_boost;
    u16 time_1;
    u16 time_2;
};
static_assert(sizeof(Options) == 0x18);

struct MapActor
{
    // Speculated official name.

    u16 id;
    struct
    {
        u16 x;
        u16 y;
    }   offset;
    u16 event_id;       // Lower byte: event id 2, higher byte: event id 1.
    u32 settings[2];    // Not u64
    u8  area;
    u8  layer;
    u8  movement_id;
    u8  link_id;
    u8  init_state;
    u8  _pad[3];
};
static_assert(sizeof(MapActor) == 0x18);

struct Location
{
    // Official name not known.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   size;
    u8  id;
    u8  _pad[3];
};
static_assert(sizeof(Location) == 0xC);

struct RailInfo
{
    // Not certain if official name.

    u8  id;
    s8  _1;
    struct
    {
        u16 start;
        u16 num;
    }   point;
    u16 flag;
    u32 _8;
};
static_assert(sizeof(RailInfo) == 0xC);

struct RailPoint
{
    // Official name not known.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    f32 speed;
    f32 accel;
    s16 delay;

    // Nabbit-related
    u16 _e;
    u8  _10;
    u8  _11;
    u8  _12;
    u8  _pad[1];
};
static_assert(sizeof(RailPoint) == 0x14);

class CourseDataFile
{
public:
    enum BlockId
    {
        cBlock_Environment      =   1 - 1,
        cBlock_Options          =   2 - 1,
        cBlock_ScrollData       =   3 - 1,
                                //  4
        cBlock_DistantViewData  =   5 - 1,
                                //  6
        cBlock_NextGoto         =   7 - 1,
        cBlock_Sprite           =   8 - 1,
        cBlock_SpriteLoadRes    =   9 - 1,
        cBlock_AreaData         =  10 - 1,
        cBlock_Location         =  11 - 1,
                                // 12
                                // 13
        cBlock_RailInfo         =  14 - 1,
        cBlock_RailPoint        =  15 - 1,
        cBlock_Num
    };

public:
    MapActor* getMapActor(u32 id, void*);
    Location* getLocation(Rect* rectOut, u8 id);
    RailInfo* getRailInfo(u8 id);
    RailPoint* getRailPoint(u32 id);

    u32 id;                             // 0
    void* blocks[cBlock_Num];           // 4
    u32 blockSizes[cBlock_Num];         // 40
    u32 blockEntryCounts[cBlock_Num];   // 7C
    u8 _B8[0x100];                      // B8
    u8 _1B8[0x100];                     // 1B8
    u8 _2B8[0x100];                     // 2B8
};
static_assert(sizeof(CourseDataFile) == 0x3B8);

class CourseData
{
    SEAD_SINGLETON_DISPOSER(CourseData)

public:
    CourseDataFile* getFile(u32 id);

    CourseDataFile files[4];
};

class LevelInfo
{
    SEAD_SINGLETON_DISPOSER(LevelInfo)

public:
    u8 world;                   // 10
    u8 level;                   // 11
    u8 file;                    // 12
    u8 entrance;                // 13
    u32 area_;                   // 14
    u32 entranceType;           // 18
    u8 destWorld;               // 1C
    u8 destLevel;               // 1D
    u8 destFile;                // 1E
    u8 destEntrance;            // 1F
    u32 destArea_;               // 20
    u32 destEntranceType;       // 24
};
