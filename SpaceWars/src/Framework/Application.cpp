#include "Framework/Application.h"
#include <SDL3/SDL.h>
#include <iostream>

namespace sw
{
	Application::Application() : m_running(true)
	{
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			std::cout << "SDL failed to initialize\n";
		}

		m_window = SDL_CreateWindow("SpaceWars", 800, 600, SDL_WINDOW_RESIZABLE);
		
		if (m_window == nullptr)
		{
			std::cout << "Window creation failed\n";
		}

		m_renderer = SDL_CreateRenderer(m_window, NULL);
		if (m_renderer == nullptr)
		{
			std::cout << "Renderer creation failed\n";
		}


	}

	void Application::Run()
	{
		SDL_Event event;
		while (m_running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_EVENT_KEY_DOWN:
						std::cout << "Key down: " << event.key.key << std::endl;
						break;
				case SDL_EVENT_QUIT:
					m_running = false;
					break;
				default:
					break;
				}
			}
		}
	}
}