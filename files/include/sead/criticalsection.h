#pragma once

struct OSThread_;
typedef struct OSThread_ OSThread;

typedef struct OSThreadQueue_ {
    OSThread *head;
    OSThread *tail;
    void *parentStruct;
    u32 reserved;
} OSThreadQueue;

struct _OSMutex;
typedef struct _OSMutex OSMutex;

typedef struct _OSMutexLink
{
    OSMutex* next;
    OSMutex* prev;
} OSMutexLink;

struct _OSMutex
{
    u32 txtTag;
    char *name;
    u32 reserved;
    OSThreadQueue queue;
    OSThread* thread;
    s32 count;
    OSMutexLink link;
};

#include "idisposer.h"

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

}
