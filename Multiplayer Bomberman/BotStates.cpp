#include "BotStates.h"
#include "BotEntity.h"
#include "Timer.h"

AIWanderState::AIWanderState(void) //: timer(new Timer)
{
	timer = new Timer;
}

AIWanderState::~AIWanderState(void)
{
	delete timer;
}

AIWanderState* AIWanderState::GetInstance()
{
	static AIWanderState instance;
	return &instance;
}

void AIWanderState::Enter(BotEntity * owner)
{
	printf("Entering AIWanderState.\n");
	owner->CreateNewDestination();
}

void AIWanderState::Execute(BotEntity * owner)
{
	static double last_time = timer->Seconds();
	double new_time = timer->Seconds();

	if ((new_time - last_time > 5) && (owner->GetPosition() == owner->GetDestination()))
	{
		last_time = timer->Seconds();
		owner->ChangeState(AIIdleState::GetInstance());
	}

	if (owner->GetPosition() == owner->GetDestination())
		owner->CreateNewDestination();
}

void AIWanderState::Exit(BotEntity * owner)
{
	printf("Exiting AIWanderState.\n");
}

// Idle state.

AIIdleState::AIIdleState() 
{
	timer = new Timer;
}

AIIdleState::~AIIdleState()	
{
	delete timer;
}
	
AIIdleState * AIIdleState::GetInstance()
{
	static AIIdleState instance;
	return &instance;
}

void AIIdleState::Enter(BotEntity * owner)
{
	printf("Entering AIIdleState.\n");
	owner->SetActive(false);
}

void AIIdleState::Execute(BotEntity * owner)
{
	static double last_time = timer->Seconds();
	double new_time = timer->Seconds();

	if (new_time - last_time > 5 && (!owner->GetActive()))
	{
		last_time = timer->Seconds();
		owner->ChangeState(AIWanderState::GetInstance());
	}
}

void AIIdleState::Exit(BotEntity * owner)
{
	owner->SetActive(true);
	printf("Exiting AIIdleState.\n");
}