#include "GameFramework/GameApplication.h"
#include "Framework/World.h"

snw::Application* GetApplication()
{
	return new sw::GameApplication{};
}

namespace sw
{


	GameApplication::GameApplication()
	{
		LoadWorld<snw::World>();
	}

}

