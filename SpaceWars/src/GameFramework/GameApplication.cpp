#include "GameFramework/GameApplication.h"
#include "Framework/World.h"
#include "Framework/Actor.h"

float x;
snw::Application* GetApplication()
{
	return new snw::GameApplication{};
	x = 0;
}

namespace snw
{


	GameApplication::GameApplication()
	{
		 weak<World> world = LoadWorld<World>();
		 actor = world.lock()->SpawnActor<Actor>();
	}

	void GameApplication::Tick(float dt)
	{
		x += dt;
		if (x > 2.f)
		{
			if (!actor.expired())
			{
				actor.lock()->Destroy();
			}
				
		}
	}

}

