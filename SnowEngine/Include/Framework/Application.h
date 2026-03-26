#pragma once
#include "Screen.h"

namespace snw
{
	class Application
	{
		public:
			Application():Application(800,600,"SnowEngineGame") {}
			Application(int width, int height, std::string_view appName);
			inline int Width()const { return m_width; }
			inline int Height()const { return m_height; }
			void Run();

			
		private:
			int m_width;
			int m_height;
			Screen m_screen;
			bool m_running;
			const float m_targetFps;
			float m_fixedDt;

			virtual void Tick(float dt);
			virtual void Render();

			void TickInternal(float dt);
			void RenderInternal();
			
	};
}