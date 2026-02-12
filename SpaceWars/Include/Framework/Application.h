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
		private:
			 SDL_Window* m_window;
			 SDL_Renderer* m_renderer;
			bool m_running;
	};
}