#ifndef SEAD_FRAMEWORK_H_
#define SEAD_FRAMEWORK_H_

//#include <framework/seadMethodTreeMgr.h>
#include <framework/seadTaskBase.h>
//#include <framework/seadTaskMgr.h>
//#include <gfx/seadFrameBuffer.h>
//#include <heap/seadArena.h>
//#include <heap/seadHeap.h>
#include <hostio/seadHostIOMgr.h>
#include <prim/seadDelegateEventSlot.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <time/seadTickSpan.h>

namespace sead {

class Arena;

class FrameBuffer;
class Heap;
class LogicalFrameBuffer;
class MethodTreeMgr;
class TaskMgr;

class Framework
{
    SEAD_RTTI_BASE(Framework)

public:
    struct CreateSystemTaskArg
    {
        inline CreateSystemTaskArg();

        HostIOMgr::Parameter* hostio_parameter;
        TickSpan infloop_detection_span;
    };
#ifdef cafe
    static_assert(sizeof(CreateSystemTaskArg) == 0x10, "sead::Framework::CreateSystemTaskArg size mismatch");
#endif // cafe

    struct InitializeArg
    {
        InitializeArg();

        u32 heap_size;
        Arena* arena;
    };
#ifdef cafe
    static_assert(sizeof(InitializeArg) == 8, "sead::Framework::InitializeArg size mismatch");
#endif // cafe

    struct RunArg
    {
        RunArg();

        u32 prepare_stack_size;
        s32 prepare_priority;
    };
#ifdef cafe
    static_assert(sizeof(RunArg) == 8, "sead::Framework::RunArg size mismatch");
#endif // cafe

    enum ProcessPriority
    {
        cProcessPriority_Idle = 0,
        cProcessPriority_Normal = 1,
        cProcessPriority_High = 2,
        cProcessPriority_RealTime = 3
    };

public:
    Framework();
    virtual ~Framework();

    virtual void run(Heap*, const TaskBase::CreateArg&, const RunArg&);
    virtual void createSystemTasks(TaskBase*, const CreateSystemTaskArg&);
    virtual FrameBuffer* getMethodFrameBuffer(s32) const = 0;
    virtual LogicalFrameBuffer* getMethodLogicalFrameBuffer(s32) const;
    virtual bool setProcessPriority(ProcessPriority);
    virtual void reserveReset(void*);
    virtual void initRun_(Heap*);
    virtual void runImpl_();
    virtual MethodTreeMgr* createMethodTreeMgr_(Heap*) = 0;
    virtual void procReset_();

    typedef DelegateEvent<void*> ResetEvent;

    bool mReserveReset;
    void* mResetParameter;
    ResetEvent mResetEvent;
    TaskMgr* mTaskMgr;
    MethodTreeMgr* mMethodTreeMgr;
    Heap* mMethodTreeMgrHeap;
};
#ifdef cafe
static_assert(sizeof(Framework) == 0x28, "sead::Framework size mismatch");
#endif // cafe

} // namespace sead

#endif // SEAD_FRAMEWORK_H_
