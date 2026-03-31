#pragma once
#include "Screen.h"
#include "Core.h"

namespace snw
{
	class World;
	class Application
	{
		public:
			Application():Application(800,600,"SnowEngineGame") {}
			Application(int width, int height, std::string_view appName);
			inline int Width()const { return m_width; }
			inline int Height()const { return m_height; }
			void Run();
			
			template <class worldType>
			weak<worldType> LoadWorld()
			{
				shared<worldType> newWorld = std::make_shared<worldType>(this);
				currentWorld = newWorld;
				return newWorld;
			}

	 protected:
			Screen m_screen;
			int m_width;
			int m_height;
		private:
			bool m_running;
			const float m_targetFps;
			float m_fixedDt;
			shared<World> currentWorld;

			virtual void Tick(float dt);
			virtual void Render();

			void TickInternal(float dt);
			void RenderInternal();
			
	};
}