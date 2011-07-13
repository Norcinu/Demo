#ifndef ENTITY_STATEMACHINE_H
#define ENTITY_STATEMACHINE_H

#include "AIState.h"
#include "AIEntity.h"
#include <cassert>

template <class T>
class StateMachine
{
public:
	StateMachine(T * owner_) : owner(owner_), current_state(nullptr), previous_state(nullptr),
		global_state(nullptr) {}

	virtual ~StateMachine(void)	{}

	void SetCurrentState(AIState<T> * s)  { current_state = s; }
	void SetGlobalState(AIState<T> * s)   { global_state = s; }
	void SetPreviousState(AIState<T> * s) { previous_state = s; }
		
	AIState<T> * CurrentState()  const { return current_state; }
	AIState<T> * GlobalState()   const { return global_state; }
	AIState<T> * PreviousState() const { return previous_state; }
		
	void Update() const
	{
		if (global_state)
			global_state->Execute(owner);

		if (current_state)
			current_state->Execute(owner);
	}
		
	void ChangeState(AIState<T> * new_state)
	{
		assert(new_state && 
        "<StateMachine::ChangeState>: trying to change to NULL state");

		previous_state = current_state;
		current_state->Exit(owner);
		current_state = new_state;
		current_state->Enter(owner);
	}

	void RevertToPreviousState() { ChangeState(previous_state); }
	
private:
	T* owner;
	AIState<T> * current_state;
	AIState<T> * previous_state;
	AIState<T> * global_state;
};

#endif
