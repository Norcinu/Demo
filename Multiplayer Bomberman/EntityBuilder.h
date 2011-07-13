#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

class BaseEntity;
struct Entity;

class EntityBuilder
{
public:
	~EntityBuilder() {}
	
	BaseEntity *GetBaseEntity();
	Entity *GetEntity();

	virtual bool Create() = 0;

protected:
	EntityBuilder() {}
	
protected:
	BaseEntity * base_entity;
	struct Entity * entity;
};


/**
	Start of PlayerBuilder
**/

class PlayerBuilder : public EntityBuilder
{
public:
	PlayerBuilder(); 
	~PlayerBuilder();

	bool Create();
};

/**
	Start of BotBuilder
**/

class BotBuilder : public EntityBuilder
{
	BotBuilder();
	~BotBuilder();

	bool Create();
};

#endif
