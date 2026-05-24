#include "GameFramework/GameApplication.h"
#include "Framework/World.h"
#include "Framework/Actor.h"
#include "GameFrameWork/ArcadeScene.h"


snw::Application* GetApplication()
{
	return new snw::GameApplication{};
	
}

namespace snw
{


	GameApplication::GameApplication()
	{
		 weak<World> world = LoadWorld<World>();
		 arcadeScene = std::make_unique<ArcadeScene>();
	}

	void GameApplication::Tick(float dt)
	{
		arcadeScene->Update(dt);
	}

	void GameApplication::Render()
	{
		
		arcadeScene->Render(m_screen);

	}

}

