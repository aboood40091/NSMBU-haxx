#pragma once

#include <heap/seadDisposer.h>

namespace nw { namespace eft {

class System;

} }

class PtclMgr
{
    SEAD_SINGLETON_DISPOSER(PtclMgr)

public:
    u8 getEmitterSetGroupID(s32 emitterSetID, u32 resourceID) const;

    nw::eft::System* system;   // 10, sead::ptcl::PtclSystem*
    // ...
};
