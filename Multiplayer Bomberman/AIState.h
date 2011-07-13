#ifndef ENTITYSTATE_H
#define ENTITYSTATE_H

//#include "AIEntity.h"

template <class T>
class AIState
{
protected:
	AIState(void) {}

public:
	virtual ~AIState(void) {}

	virtual void Enter(T * owner) = 0;
	virtual void Execute(T * owner) = 0;
	virtual void Exit(T * owner) = 0;
};

#endif
