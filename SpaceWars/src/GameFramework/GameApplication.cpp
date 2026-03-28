#include "GameFramework/GameApplication.h"
#include "Framework/World.h"
#include "Framework/Actor.h"

snw::Application* GetApplication()
{
	return new snw::GameApplication{};
}

namespace snw
{


	GameApplication::GameApplication()
	{
		 weak<World> world = LoadWorld<World>();
		 world.lock()->SpawnActor<Actor>();
	}

}

