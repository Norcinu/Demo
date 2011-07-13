#include <iostream>

#include "Engine.h"
#include "SplashState.h"

int main(int argc, char *argv[])
{
	Engine *engine = new Engine;
	if (!engine->Initialise())
		return -1;
	
	engine->ChangeState(SplashState::GetInstance());

	while (engine->IsRunning())
	{
		engine->HandleEvents();
		engine->Update();
		engine->Render();
	}

	delete engine;
	return 0;
}
