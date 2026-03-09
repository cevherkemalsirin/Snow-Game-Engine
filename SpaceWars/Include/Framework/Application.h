#pragma once
#include "Screen.h"

namespace sw
{
	class Application
	{
		public:
			Application(int width, int height, std::string_view appName);
			inline int Width()const { return m_width; }
			inline int Height()const { return m_height; }
			void Run();
			void Tick(float dt);
			void Render();
			
		private:
			int m_width;
			int m_height;
			Screen m_screen;
			bool m_running;
			const float m_targetFps;
			float m_fixedDt;

	};
}