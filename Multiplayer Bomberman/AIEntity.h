#ifndef AIENTITY_H
#define AIENTITY_H

#include "baseentity.h"
#include "AStar.h"
#include "AIState.h"
#include "StateMachine.h"

class AIEntity : public BaseEntity
{
public:
	AIEntity(void);
	AIEntity(const EntityImpl_t& ei);
	~AIEntity(void);

	void CreateNewDestination();

	void OnCollision(const BaseEntity *ent) {}
	void Update() {}
	void Render(const double dt, Visualisation * vis) {}
	void DoAnimation() {}

protected:
	/*AIState<AIEntity> * current_state;
	AIState<AIEntity> * previous_state;*/
//	StateMachine<AIEntity> * state_machine;
	std::vector<node_t> path;
};

#endif
