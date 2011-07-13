#ifndef BOTENTITY_H
#define BOTENTITY_H

#include "AIEntity.h"
#include "StateMachine.h"
#include "AIState.h"

class BotEntity;


class BotEntity : public AIEntity
{
public:
	BotEntity(void);
	BotEntity(const EntityImpl_t& ei);
	BotEntity(Level * l);

	~BotEntity(void);

	void OnCollision(const BaseEntity *ent);
	void Update();
	void Render(const double dt, Visualisation * vis);
	void DoAnimation();
	void ChangeState(AIState<BotEntity> * new_state);

private:
	StateMachine<BotEntity> * state_machine;
//	AIState * current_state;
//	AIState * previous_state;
//	std::vector<node_t> path;
};

#endif
