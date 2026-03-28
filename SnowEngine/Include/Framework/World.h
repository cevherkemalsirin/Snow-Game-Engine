#pragma once
#include "framework/Core.h"

/*
* This class represent the game world. It has one or more levels/Maps
* It owns every actor current level has, it spawns them, it destroys them etc.
*/

namespace snw
{
	class Actor;
	class Application;
	class World
	{
	private:
		Application* m_owningApplication;
		bool m_beganPlay;
		List<shared<Actor>> m_Actors;
		//if we are looping through m_Actors we do not want to add new actors during this
		List<shared<Actor>> m_PendingActors;


		void BeginPlay();
		void Tick(float deltaTime);
	public:
		World(Application* owningApplication);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);


		template<class actorType>
		weak<actorType> SpawnActor()
		{
			shared<actorType> newActor = std::make_shared<actorType>(this);
			m_PendingActors.push_back(newActor);
			return newActor;
		}


		virtual ~World();
		
	};
}