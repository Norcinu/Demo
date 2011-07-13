#ifndef PLAYERSTATES_H
#define PLAYERSTATES_H

#include "AIState.h"

class Timer;
class BotEntity;

class AIWanderState : public AIState<BotEntity>
{
public:
	~AIWanderState(void);

	static AIWanderState * GetInstance();
	void Enter(BotEntity * owner);
	void Execute(BotEntity * owner);
	void Exit(BotEntity * owner);
	
private:
	AIWanderState(void);
	AIWanderState(const AIWanderState& rhs);
	AIWanderState& operator=(const AIWanderState& rhs);

private:
	Timer * timer;
};

class AIIdleState : public AIState<BotEntity>
{
public:
	~AIIdleState();

	static AIIdleState * GetInstance();
	void Enter(BotEntity * owner);
	void Execute(BotEntity * owner);
	void Exit(BotEntity * owner);

private:
	AIIdleState();
	AIIdleState(const AIIdleState& rhs);
	AIIdleState& operator=(const AIIdleState& rhs);

private:
	Timer * timer;
};

#endif
