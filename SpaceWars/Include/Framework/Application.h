#pragma once

struct SDL_Window;
struct SDL_Renderer;
namespace sw
{
	class Application
	{
		public:
			Application();
			void Run();
			void Tick(float dt);
			void Render();
		private:
			 SDL_Window* m_window;
			 SDL_Renderer* m_renderer;
			bool m_running;
			const float m_targetFps;
			float m_fixedDt;
	};
}