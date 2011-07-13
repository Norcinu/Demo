#include "World.h"
#include "Visualisation.h"
#include "Timer.h"
#include "Level.h"
#include "EntityImpl.h"
#include "BaseEntity.h"
#include "PlayerEntity.h"
#include "BotEntity.h"
#include "BombEntity.h"
#include "Explosion.h"
#include "maths.h"
#include "Messenger.h"
#include "EntitySystem.h"
#include "BotStates.h"

#include <algorithm>
#include <fstream>
#include <boost\bind.hpp>

EntitySystem entity_system;
Entity game_entities[MAX_PLAYERS];

int id = 0; 

World::World(void) : 
	game_timer(new Timer), 
	current_level(nullptr), 
	messages(nullptr),
	update_delta(0.0), 
	tick_rate(100)
{
	entities.reserve(MAX_PLAYERS);
	spawns.reserve(MAX_SPAWNPOINTS);
	bomb_list.reserve(MAX_BOMBS);
	explosion_list.reserve(NUM_EXPLOSIONS);
}

World::World(Messenger * msg) : game_timer(new Timer), current_level(nullptr), update_delta(0.0), tick_rate(50),
	messages(msg)
{
}

World::~World(void)
{
	CleanUp();
}

bool World::Initialise(const std::string& assets, Visualisation * vis)
{
	std::cout << "world->init";
	current_level = new Level;//(32, 32, 20, 15);
	if (current_level == nullptr)
		return false;

	int gid1 = 0;
	if (!vis->AddSprite(&gid1, std::string("data\\bitmaps\\brick.spr")))
		return false;

	int gid2 = 0;
	if (!vis->AddSprite(&gid2, std::string("data\\bitmaps\\destroyable_brick.spr")))
		return false;
	
	if (!current_level->LoadData(assets, gid1, gid2))
		return false;

	current_level->GetSpawnPoints(spawns);
	
	if (!vis->AddSprite(&gid1, std::string("data\\bitmaps\\sprite.spr")))
		return false;

	AddPlayer(gid1);
	AddPlayer(gid1);
	
	if (!vis->AddSprite(&gid1, std::string("data\\bitmaps\\bomb.spr")))
		return false;
	
	return true;
}

void World::CleanUp()
{
	for (ent_itor it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	for (bomb_itor it = bomb_list.begin(); it != bomb_list.end(); ++it)
		delete *it;

	for (explosion_itor it = explosion_list.begin(); it != explosion_list.end(); it)
		delete *it;

	if (game_timer != nullptr)
		delete game_timer;

	if (current_level != nullptr)
		delete current_level;
}

bool World::IsCollideable(const BaseEntity* ent1, const BaseEntity* ent2) const
{
	return true;
}

bool World::CheckBounds(const int id) const
{
	if (id < 0 && id > (int)entities.size()-1)
		return false;
	else
		return true;
}
void World::Move(const int id, const math::Vector2& direction)
{
	if (CheckBounds(id)) 
	{
		entities[id]->Move(direction);
		entities[id]->DoAnimation();
	}

	/*game_entities[id].GetAs<Position2D>()->position += direction;
	game_entities[id].GetAs<Position2D>()->previous_position = */
}

void World::Action(const int id)
{
	if (CheckBounds(id))
	{
		for(size_t i = 0; i<bomb_list.size(); ++i)
		{
			if (!bomb_list[i]->GetActive())
			{
				bomb_list[i]->SetActive(true);
				bomb_list[i]->SetPosition(entities[id]->GetPosition());
				bomb_list[i]->SetSide(entities[id]->GetSide());
				break;
			}
		}
	}
}

void World::Update()
{
	while (!messages->IsEmpty())
	{
		EventMessage_t msg = messages->PopFront();
		ParseMessage(msg);
	}

	if (game_timer->Milliseconds() - update_delta > tick_rate)
	{
		std::for_each(entities.begin(), entities.end(), [](BaseEntity* ent) { ent->Update(); });
		std::for_each(bomb_list.begin(), bomb_list.end(), [](BombEntity *b) { b->Update(); });

		update_delta = game_timer->Milliseconds();
	}

//	MyFSM *st=new MyFSM;
//	st->state_machine = new entityFSM::StateMachine<Entity>(&game_entities[1]);

	//st->state_machine.ChangeState(entityFSM::State<&game_entities[1]>);
	//Position2D *pos=entity_system[0].getAs<Position2D>();
}

void World::Render(Visualisation* vis) const
{
	double delta = (game_timer->Milliseconds() / update_delta) / tick_rate;
	
	vis->BeginScene();
	current_level->Render(vis);
	
	std::for_each(bomb_list.begin(), bomb_list.end(), [&delta, &vis](BombEntity *bomb) -> void 
	{
		if (bomb->GetActive()) 
		{ 
			bomb->Render(delta, vis); 
		}
	});

	// draw active players
	std::for_each(entities.begin(), entities.end(), [&delta, &vis](BaseEntity *ent) -> void
	{
		/*if (ent->GetActive())
		{*/
			ent->Render(delta, vis);
		//}
	});

	vis->EndScene();
}

bool World::ChangeLevel(const std::string& level_name)
{
	if (current_level != nullptr)
	{
		delete current_level;
		current_level = new Level;
		
		if (!current_level->LoadData(level_name, 0, 1))
			return false;
		
		// all successful.
		return true;
	}
	else
		return false;
}

math::Vector2& World::FindFirstSpawn() const
{
	auto itor = std::find_if(spawns.begin(), spawns.end(), [](const SpawnPoint_t* sp) -> bool { 
		std::cout << "Testing if position is free " << sp->position << std::endl;
		return sp->is_available; 
	});

	(*itor)->is_available = false;
	return (*itor)->position;
}

void World::AddPlayer(const int id, bool is_bot)
{
	EntityImpl_t temp;
	temp.graphic_id = id;
	temp.direction = LEFT;
	temp.animation_frame = 7;
	temp.position = FindFirstSpawn();
	temp.previous_position = temp.position;
	temp.active = true;
	temp.level_copy = current_level;
	temp.path_finder = new AStar(temp.level_copy);

	BotEntity *p = new BotEntity(temp);
	//p->SetFSM(new entityFSM::StateMachine<BaseEntity>(p));
	entities.push_back(p);

	
	///----------- NEW ENTITY SYSTEM
	// Components used by every entity.
	//static int index = 0;
	//Position2D *position = new Position2D;
	//Drawable *drawable = new Drawable;
	//Collision *collision = new Collision;

	//entity_system.AddComponent(&game_entities[index], position);
	//entity_system.AddComponent(&game_entities[index], drawable);
	//entity_system.AddComponent(&game_entities[index], collision);

	//// Components for non-players entities.
	//// assume player is always entity 0.
	//if (is_bot)
	//{
	//	MyFSM *fsm = new MyFSM;
	//	Pathfinder *pf = new Pathfinder;
	//	
	//	entity_system.AddComponent(&game_entities[index], fsm);
	//	entity_system.AddComponent(&game_entities[index], pf);
	//} 
	//++index;
}

void World::FreeSpawnPoint(const math::Vector2& position)
{
	auto itor = std::find_if(spawns.begin(), spawns.end(), [position](SpawnPoint_t* sp) -> bool { 
		std::cout << "Testing if position is free " << sp->position << std::endl;
		return sp->position == position; 
	});

	(*itor)->is_available = true;
}

void World::CreateBombList(const int id)
{
	for (int i = 0; i < MAX_BOMBS; ++i)
	{
		/*BombEntity *b = new BombEntity;
		b->SetActive(false);
		b->SetSide(NONE);
		b->SetGraphicID(id);
		bomb_list.push_back(b);*/
	}
}

void World::ResetBomb(const int id)
{
	bomb_list[id]->SetActive(false);
	bomb_list[id]->SetSide(NONE);
	bomb_list[id]->SetPosition(math::Vector2(0,0));
}

void World::CreateExplosionList(const int id)
{
	for (int i = 0; i<NUM_EXPLOSIONS; ++i)
	{
		Explosion *e = new Explosion;
		explosion_list.push_back(e);
	}
}

void World::ParseMessage(const EventMessage_t& msg)
{
	switch (msg.event_type)
	{
	case EventMessage_t::DROP_BOMB:
		Action(msg.id);
		break;
	case EventMessage_t::FORWARD:
		entities[msg.id]->Move(math::Vector2(0, -4));
		entities[msg.id]->DoAnimation();
		break;
	case EventMessage_t::BACK:
		entities[msg.id]->Move(math::Vector2(0, 4));
		entities[msg.id]->DoAnimation();
		break;
	case EventMessage_t::LEFT:
		entities[msg.id]->Move(math::Vector2(-4, 0));
		entities[msg.id]->DoAnimation();
		break;
	case EventMessage_t::RIGHT:
		entities[msg.id]->Move(math::Vector2(4, 0));
		entities[msg.id]->DoAnimation();
		break;
	}
}