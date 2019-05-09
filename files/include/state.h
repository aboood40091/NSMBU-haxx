#pragma once

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

class StateClass {
public:
	void *stateMgr;
	unsigned int beginSomething;
	unsigned int executeSomething;
	unsigned int defaultSomething;

	void executeState();
};

template <class TOwner>
class StateMgrBase : public StateMgrVirt<TOwner> {
public:
	void *executeRelated;
	TOwner *owner;
	unsigned int _C;
	StateClass stateClass;
	unsigned int _20;
};
