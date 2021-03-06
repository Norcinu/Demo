#include "Events.h"
#include "World.h"
#include "Messenger.h"
#include "maths.h"
#include <string>
#include <boost\timer.hpp>


Events::Events(void) : running(true)
{	
	keymapping.insert(std::make_pair(SDLK_w, EVT_FORWARD));
	keymapping.insert(std::make_pair(SDLK_s, EVT_BACKWARD));
	keymapping.insert(std::make_pair(SDLK_a, EVT_LEFT));
	keymapping.insert(std::make_pair(SDLK_d, EVT_RIGHT));
	keymapping.insert(std::make_pair(SDLK_SPACE, EVT_ACTION));
	keymapping.insert(std::make_pair(SDLK_g, EVT_TOGGLE_SOUND_STREAM));
	keymapping.insert(std::make_pair(SDLK_UP, EVT_VOLUME_UP));
	keymapping.insert(std::make_pair(SDLK_DOWN, EVT_VOLUME_DOWN));
	keymapping.insert(std::make_pair(SDLK_RIGHT, EVT_NEXT_SONG));
	keymapping.insert(std::make_pair(SDLK_LEFT, EVT_PREVIOUS_SONG));

	for (int i = 0; i < NUM_OF_KEYS-1; ++i)
		key_table[i] = false;

	SDL_EnableKeyRepeat(170,70);
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}


Events::~Events(void)
{
}

//void Events::Update(World * world)
void Events::Update(Messenger * msg)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			std::map<char, INPUT_EVENTS>::const_iterator it = keymapping.begin();
			char sc = event.key.keysym.sym;
			it = keymapping.find(sc);
	
			if (it != keymapping.end())
			{
				EventMessage_t msg_to_send;
				switch (it->second)
				{
				case EVT_ACTION:
					FillMessage(&msg_to_send, 0, EventMessage_t::DROP_BOMB);					
					msg->AddMessage(msg_to_send);
					break;
				case EVT_FORWARD:
					FillMessage(&msg_to_send, 0, EventMessage_t::FORWARD);
					msg->AddMessage(msg_to_send);
					break;
				case EVT_BACKWARD:
					FillMessage(&msg_to_send, 0, EventMessage_t::BACK);
					msg->AddMessage(msg_to_send);
					break;
				case EVT_LEFT:
					FillMessage(&msg_to_send, 0, EventMessage_t::LEFT);
					msg->AddMessage(msg_to_send);
					break;
				case EVT_RIGHT:
					FillMessage(&msg_to_send, 0, EventMessage_t::RIGHT);
					msg->AddMessage(msg_to_send);
					break;
				}
			}
		}
		
		if (event.type==SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			running=false;
	}
}

void Events::SetKeyMap()
{
	keymapping.clear();

	std::string line = "";

	while (line.empty())
	{
		std::getline(std::cin, line); 
	}

	keymapping.insert(std::make_pair(line[0], EVT_FORWARD));
	keymapping.insert(std::make_pair(line[1], EVT_BACKWARD));
	keymapping.insert(std::make_pair(line[2], EVT_LEFT));
	keymapping.insert(std::make_pair(line[3], EVT_RIGHT));
	keymapping.insert(std::make_pair(line[4], EVT_ACTION));

	// AND SO ON.
}

void Events::FillMessage(EventMessage_t *out, const int id, const EventMessage_t::EventType ev)
{
	out->id = id;
	out->event_type = ev;
	out->time_stamp = my_timer.elapsed();
}