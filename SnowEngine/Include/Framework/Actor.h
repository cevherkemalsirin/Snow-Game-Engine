#pragma once


namespace snw
{
	class World;
	class Actor
	{
	private:
		World* m_owningWorld;
		bool m_beganPlay;



	public:
		Actor(World* owningWorld);

		void BeginPlayInternal();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		virtual ~Actor();
	};
}