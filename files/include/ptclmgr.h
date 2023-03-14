#pragma once

#include <heap/seadDisposer.h>

#include <nw/eft/eft_System.h>

class PtclMgr
{
    SEAD_SINGLETON_DISPOSER(PtclMgr)

public:
    u8 getEmitterSetGroupID(s32 emitterSetID, u32 resourceID = 0) const;

    nw::eft::System* system;   // 10, sead::ptcl::PtclSystem*
    // ...
};
