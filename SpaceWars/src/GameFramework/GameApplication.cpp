#include "GameFramework/GameApplication.h"
#include "Framework/World.h"
#include "Game/BreakOut/BreakOut.h"
#include "Game/GameScene.h"
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
		 m_arcadeScene = std::make_unique<ArcadeScene>();
		 PushScene(std::move(m_arcadeScene));

		 //temp
		 {
			 std::unique_ptr<BreakOut> breakOutGame = std::make_unique<BreakOut>();
			 std::unique_ptr<GameScene> breakOutScene = std::make_unique<GameScene>(std::move(breakOutGame));
			 PushScene(std::move(breakOutScene));
		 }
	}

	void GameApplication::Tick(float dt)
	{
		if (TopScene())
		{
			TopScene()->Tick(dt);
		}
		
	}

	void GameApplication::Render()
	{
		if (TopScene())
		{
			TopScene()->Render(m_screen);
		}
	}

	void GameApplication::PushScene(unique<Scene> scene)
	{
		if (!scene) return;
		scene->Init();
		m_inputController.SetGameController(scene->GetGameController());
		m_sceneStack.emplace_back(std::move(scene));
		m_screen.UpdateScreenTitle(TopScene()->GetSceneName());
		
	}

	void GameApplication::PopScene()
	{
		if (m_sceneStack.size() > 1)
		{
			m_sceneStack.pop_back();
		}
		if (TopScene())
		{
			m_screen.UpdateScreenTitle(TopScene()->GetSceneName());
			m_inputController.SetGameController(TopScene()->GetGameController());
		}
	}

	Scene* GameApplication::TopScene()
	{
		if (m_sceneStack.empty())
		{
			return nullptr;
		}
		return m_sceneStack.back().get();
	}

}

