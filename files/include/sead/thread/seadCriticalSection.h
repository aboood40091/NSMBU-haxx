#ifndef SEAD_CRITICAL_SECTION_H_
#define SEAD_CRITICAL_SECTION_H_

#include <dynamic_libs/os_types.h>

#include <heap/seadDisposer.h>

namespace sead {

class CriticalSection : public IDisposer
{
public:
    CriticalSection();
    virtual ~CriticalSection();

    void lock();
    bool tryLock();
    void unlock();

    OSMutex mCriticalSectionInner;
};

} // namespace sead

#endif // SEAD_CRITICAL_SECTION_H_
