#include "BotEntity.h"
#include "Visualisation.h"
#include "AIState.h"
#include "BotStates.h"
#include "EntityImpl.h"
#include "Level.h"
#include "StateMachine.h"

#include <boost\thread.hpp>
#include <boost\bind.hpp>

const int speed = 2;

BotEntity::BotEntity(void)
{
	impl = new EntityImpl_t;
	state_machine = new StateMachine<BotEntity>(this);
	state_machine->SetCurrentState(AIWanderState::GetInstance());
}

BotEntity::BotEntity(const EntityImpl_t& ei)
{
	impl = new EntityImpl_t(ei);
	state_machine = new StateMachine<BotEntity>(this);
	state_machine->SetCurrentState(AIWanderState::GetInstance());
}

BotEntity::BotEntity(Level * l)
{
	 impl = new EntityImpl_t(l);
	 state_machine = new StateMachine<BotEntity>(this);
	 state_machine->SetCurrentState(AIWanderState::GetInstance());
}

BotEntity::~BotEntity(void)
{
	delete state_machine;
}

void BotEntity::ChangeState(AIState<BotEntity> * new_state)
{
	state_machine->ChangeState(new_state);
}

void BotEntity::DoAnimation()
{
	if (impl->direction == LEFT)
	{
		if (impl->animation_position.x == 192)
			impl->animation_position.x = 224;
		else
			impl->animation_position.x = 192;
	}

	if (impl->direction == RIGHT)
	{
		if ( impl->animation_position.x == 64 )
			impl->animation_position.x = 96;
		else
			impl->animation_position.x = 64;
	}
	
	if (impl->direction == BACKWARD)
	{
		if ( impl->animation_position.x == 128 )
			impl->animation_position.x = 160;
		else
			impl->animation_position.x = 128;
	}
	
	if (impl->direction == FORWARD)
	{
		if ( impl->animation_position.x == 0 )
			impl->animation_position.x = 32;
		else
			impl->animation_position.x = 0;
	}
}

void BotEntity::OnCollision(const BaseEntity * ent)
{
}

void BotEntity::Update()
{
	//if (impl->active)
	//{
		//current_state->Execute(this);
	state_machine->Update();

		if (path.size() == 0 && impl->active)
		{
			//impl->moving = true;
			boost::thread t(boost::bind(&AStar::Search, impl->path_finder, boost::ref(path),
				impl->position, impl->destination));
			t.join();
		}

		if (path.size() > 0)
		{
			//impl->moving = false;
			int x = abs(impl->position.x - path.back().position.x);
			int y = abs(impl->position.y - path.back().position.y);

			math::Vector2 dir(path.back().position - impl->position);
			
			dir.x = math::Clamp<float>(dir.x,-1,1);
			dir.y = math::Clamp<float>(dir.y,-1,1);

			math::Vector2 temp = impl->position;

			if (speed >= x)
				temp.x = path.back().position.x;
			else 
				temp.x += speed * dir.x;

			if (speed >= y)
				temp.y = path.back().position.y;
			else
				temp.y += speed * dir.y;

			if (temp == path.back().position)
				path.pop_back();

			impl->previous_position = impl->position;
			impl->position = temp;	
			
			if (dir.x == 1)
				impl->direction = RIGHT;
			else if (dir.x == -1)
				impl->direction = LEFT;
			else if (dir.y == 1)
				impl->direction = BACKWARD;
			else
				impl->direction = FORWARD;

			DoAnimation();
		}
	//}
}

void BotEntity::Render(const double dt, Visualisation * vis)
{
	math::Vector2 lerped;
	lerped.Lerp(impl->position, impl->previous_position, dt);
	vis->DrawSprite(impl->graphic_id, impl->animation_position, lerped);
}