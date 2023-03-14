#ifndef EFT_HANDLE_H_
#define EFT_HANDLE_H_

#include <nw/eft/eft_EmitterSet.h>

namespace nw { namespace eft {

class EmitterSet;

class Handle
{
public:
    Handle()
        : mEmitterSet(NULL)
    {
    }

    void Invalidate()
    {
        mEmitterSet = NULL;
    }

    EmitterSet* GetEmitterSet()
    {
        return mEmitterSet;
    }

    const EmitterSet* GetEmitterSet() const
    {
        return mEmitterSet;
    }

    bool IsValid() const
    {
        return mEmitterSet != NULL && mCreateID == mEmitterSet->GetCreateID();
    }

private:
    EmitterSet*         mEmitterSet;
    u32                 mCreateID;

    friend class System;
};
static_assert(sizeof(Handle) == 8, "nw::eft::Handle size mismatch");

} } // namespace nw::eft

#endif // EFT_HANDLE_H_
