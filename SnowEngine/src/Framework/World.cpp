
#include "Framework/World.h"
#include "Framework/Actor.h"

namespace snw
{
	World::World(Application* owningApplication) :m_owningApplication(owningApplication), m_beganPlay(false), m_Actors{}, m_PendingActors{}
	{

	}
	void World::BeginPlay()
	{
		LOG("World BeginPlay is called");
	}

	void World::Tick(float deltaTime)
	{

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
		for (auto actor : m_PendingActors)
		{
			m_Actors.push_back(actor);
			actor->BeginPlayInternal();
		}
		m_PendingActors.clear();

		for (auto actor : m_Actors)
		{
			actor->Tick(deltaTime);
		}

		Tick(deltaTime);
	}

	World::~World()
	{
	}
}

