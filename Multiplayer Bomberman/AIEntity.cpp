#include "AIEntity.h"
#include "AIState.h"
#include "BotStates.h"
#include "EntityImpl.h"


AIEntity::AIEntity(void) //: state_machine(new StateMachine<AIEntity>(this))
{
	//state_machine->SetCurrentState(AIWanderState::GetInstance());
}

AIEntity::~AIEntity(void)
{
	//delete state_machine;
}

//void AIEntity::ChangeState(AIState<BotEntity> * new_state)
//{
//	//state_machine->ChangeState(new_state);
//	/*previous_state = current_state;
//	current_state->Exit(this);
//	current_state = new_state;
//	current_state->Enter(this);*/
//}

void AIEntity::CreateNewDestination()
{
	impl->destination = impl->level_copy->GetRandomWalkableTile();
}
