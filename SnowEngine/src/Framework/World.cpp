#include "Framework/World.h"
#include "Framework/Core.h"

namespace snw
{
	void World::BeginPlay()
	{
		LOG("began play");
	}

	void World::Tick(float deltaTime)
	{
		LOG("Ticking at: {}", 1/deltaTime);
	}

	void World::BeginPlayInternal()
	{
		if (!m_beganPlay)
		{
			m_beganPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	World::~World()
	{
	}
}

