#pragma once
#include <Framework/Application.h>

class ArcadeScene;
class Scene;
namespace snw
{
	class Actor;
	class GameApplication : public Application
	{
	private:
		unique<ArcadeScene> m_arcadeScene;
		std::vector<unique<Scene>> m_sceneStack;
	public:
		GameApplication();


		virtual void Tick(float dt) override;
		virtual void Render() override;

		void PushScene(unique<Scene> scene);
		void PopScene();
		Scene* TopScene();

	};
}