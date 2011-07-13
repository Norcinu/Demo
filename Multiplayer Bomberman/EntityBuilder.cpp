#include "EntityBuilder.h"
#include "EntitySystem.h"
#include "BaseEntity.h"

PlayerBuilder::PlayerBuilder()
{
	 entity = new Entity;
}

PlayerBuilder::~PlayerBuilder()
{
	delete entity;
}

bool PlayerBuilder::Create()
{
	//entity->entity_system->AddComponent(entity, 
	return true;
}