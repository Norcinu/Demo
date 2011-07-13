#ifndef ENTITYIMPL_H
#define ENTITYIMPL_H

#include "maths.h"
#include "Rectangle.h"
#include "Level.h"
#include "types.h"
#include "AStar.h"

struct EntityImpl_t
{
	bool active;
	bool moving;

	int id;
	int graphic_id;
	int animation_frame;
	int health;

	Level * level_copy;
	AStar * path_finder;

	EntitySide side;
	EntityDirection direction;

	math::Vector2 position;
	math::Vector2 previous_position;
	math::Vector2 animation_position;
	math::Vector2 destination;

	rec::Rectangle collision_box;

	EntityImpl_t() : active(false), moving(false), id(0), graphic_id(0), animation_frame(0), side(NONE), health(100),
		direction(FORWARD), position(), previous_position(), destination(), collision_box(), animation_position(), 
		level_copy(new Level), path_finder(new AStar){}

	EntityImpl_t(Level * l) : active(false), moving(false), id(0), graphic_id(0), animation_frame(0), side(NONE), health(100),
		direction(FORWARD), position(), previous_position(), collision_box(), animation_position(), level_copy(new Level(l)),
		path_finder(new AStar(level_copy)), destination(){}

	EntityImpl_t(const EntityImpl_t& e) : active(e.active), moving(e.moving), id(e.id), graphic_id(e.graphic_id), 
		animation_frame(e.animation_frame), side(e.side), direction(e.direction), position(e.position), health(e.health),
		previous_position(e.previous_position), collision_box(e.collision_box), animation_position(e.animation_position),
		level_copy(e.level_copy), path_finder(e.path_finder), destination(e.destination) {}

	~EntityImpl_t() 
	{
		/*if (level_copy)
			delete level_copy*/
		//delete state_machine;
	}
};

#endif
