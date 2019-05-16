#pragma once

#define DECLARE_STATE(CLASS, NAME) \
    static State<CLASS> StateID_##NAME; \
    void beginState_##NAME(); \
    void executeState_##NAME(); \
    void endState_##NAME();

#define CREATE_STATE(CLASS, NAME) \
    State<CLASS> CLASS::StateID_##NAME \
        (&CLASS::beginState_##NAME, \
        &CLASS::executeState_##NAME, \
        &CLASS::endState_##NAME);

extern unsigned int CurrentStateID;

class StateBase {
public:
    unsigned int id;

    virtual ~StateBase();
    virtual unsigned int getStateId();
};

template <class TOwner>
class State : public StateBase {
public:
    typedef void (TOwner::*funcptr)();
    State(funcptr begin, funcptr execute, funcptr end) {
        id = ++CurrentStateID;
        beginState = begin;
        executeState = execute;
        endState = end;
    };

    funcptr beginState;
    funcptr executeState;
    funcptr endState;
};

template <class TOwner>
class StateMgrVirt {
    virtual void vf0C();
    virtual void *beginState(State<TOwner> *);
    virtual void endState();
    virtual void *changeState(State<TOwner> *);
    virtual void clearState(void *);
    virtual void beginRelated(void *);
};

template <class TOwner> class StateMgr;

template <class TOwner>
class StateClass {
public:
    void *stateMgr;
    unsigned int beginSomething;
    unsigned int executeSomething;
    unsigned int defaultSomething;

    void executeState();
    State<TOwner> *getCurrentState();
};

template <class TOwner>
class StateMgrBase : public StateMgrVirt<TOwner> {
public:
    void *executeRelated;
    TOwner *owner;
    unsigned int _C;
    StateClass<TOwner> stateClass;
    unsigned int _20;
};

template <class TOwner>
class StateMgr : public StateMgrBase<TOwner> {
public:
    void *_24;
};
