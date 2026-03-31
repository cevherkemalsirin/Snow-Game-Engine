#pragma once
#include <Framework/Application.h>

namespace snw
{
	class Actor;
	class GameApplication : public Application
	{
	public:
		GameApplication();

		virtual void Tick(float dt) override;
		virtual void Render() override;
		weak<Actor> actor;
	};
}