#include "BombEntity.h"
#include "EntityImpl.h"
#include "Visualisation.h"
#include "Timer.h"

BombEntity::BombEntity(void)
{
	impl = new EntityImpl_t;
	timer = new Timer;
}

BombEntity::BombEntity(const EntityImpl_t& ei)
{
	impl = new EntityImpl_t(ei);
}

BombEntity::~BombEntity(void)
{
	if (impl)
		delete impl;

	delete timer;
}

void BombEntity::DoAnimation()
{
}

void BombEntity::OnCollision(const BaseEntity* ent)
{

}

void BombEntity::Update()
{
}

void BombEntity::Render(const double dt, Visualisation * vis)
{
	if (impl->active)
		vis->DrawSprite(impl->graphic_id, impl->animation_position, impl->position);
}
