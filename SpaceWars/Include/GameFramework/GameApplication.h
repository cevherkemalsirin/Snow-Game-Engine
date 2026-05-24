#pragma once
#include <Framework/Application.h>

class ArcadeScene;
namespace snw
{
	class Actor;
	class GameApplication : public Application
	{
	public:
		GameApplication();
		unique<ArcadeScene> arcadeScene;

		virtual void Tick(float dt) override;
		virtual void Render() override;
	};
}