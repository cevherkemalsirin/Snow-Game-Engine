#include "Framework/Actor.h"
#include "Framework/World.h"
#include "Framework/Core.h"

namespace snw
{
	void Actor::BeginPlayInternal()
	{
		if (!m_beganPlay)
		{
			m_beganPlay = true;
			BeginPlay();
		}
	}
	Actor::Actor(World* owningWorld) : m_owningWorld(owningWorld), m_beganPlay(false)
	{
	
	}

	void Actor::BeginPlay()
	{
		LOG("Actor beginPlay is called");
	}

	void Actor::Tick(float deltaTime)
	{
	}

	Actor::~Actor()
	{
		LOG("Actor Destroyed");

	}


}
