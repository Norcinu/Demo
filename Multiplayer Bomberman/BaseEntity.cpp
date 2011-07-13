#include "BaseEntity.h"
#include "EntityImpl.h"
#include "Visualisation.h"
#include "Level.h"
#include "AIState.h"

BaseEntity::BaseEntity() : impl(new EntityImpl_t)
{
}

BaseEntity::BaseEntity(const EntityImpl_t& ei) : impl(new EntityImpl_t(ei)) 
{
}

BaseEntity::BaseEntity(Level * l) : impl(new EntityImpl_t(l))
{
}

BaseEntity::~BaseEntity(void)
{
}

void BaseEntity::DropBomb()
{
}

void BaseEntity::Move(const math::Vector2& dir)
{
	if (dir.x == 4)
		impl->direction = RIGHT;
	else if (dir.x == -4)
		impl->direction = LEFT;
	else if (dir.y == 4)
		impl->direction = BACKWARD;
	else
		impl->direction = FORWARD;

	// do world collision here.
	math :: Vector2 checker;
	checker.x = impl->position.x + dir.x;
	checker.y = impl->position.y + dir.y;

	if (impl->level_copy->CheckTile(checker, impl->collision_box))
	{
		impl->previous_position = impl->position;
		impl->position += dir;
	}
}

bool BaseEntity::GetActive() const
{
	return impl->active;
}

void BaseEntity::SetActive(const bool ac)
{
	impl->active = ac;
}

math::Vector2& BaseEntity::GetPosition() const
{
	return impl->position;
}

int BaseEntity::GetID() const
{
	return impl->id;
}

int BaseEntity::GetGraphicID() const
{
	return impl->id;
}

void BaseEntity::SetGraphicID(const int gid) 
{
	impl->graphic_id = gid;
}

void BaseEntity::SetID(const int id)
{
	impl->id = id;
}

rec::Rectangle& BaseEntity::GetCollisionBox() const
{
	return impl->collision_box;
}

void BaseEntity::SetCollisionBox(const rec::Rectangle& other)
{
	impl->collision_box = other;
}

void BaseEntity::SetPosition(const math::Vector2& position)
{
	impl->position = position;
}

void BaseEntity::SetSide(const EntitySide side)
{
	impl->side = side;
}

EntitySide BaseEntity::GetSide() const
{
	return impl->side;
}

math::Vector2& BaseEntity::GetDestination() const
{
	return impl->destination;
}

void BaseEntity::SetMoving(const bool moving)
{
	impl->moving = moving;
}

bool BaseEntity::GetMoving() const
{
	return impl->moving;
}