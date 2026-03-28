#pragma once



namespace snw
{
	class Application;
	class World
	{
	private:
		Application* m_owningApplication;
		bool m_beganPlay;

		void BeginPlay();
		void Tick(float deltaTime);
		
	public:
		World(Application* owningApplication):m_owningApplication(owningApplication), m_beganPlay(false){}

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		virtual ~World();
		
	};
}