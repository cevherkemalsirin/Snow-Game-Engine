#include "Framework/Application.h"
#include <SDL3/SDL.h>
#include <iostream>

namespace sw
{
	Application::Application() : m_running(true), m_targetFps(60.0f), m_fixedDt(1.0f / m_targetFps)
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
		float accumulatedTime = 0.0f;
		double frec = static_cast<double>(SDL_GetPerformanceFrequency());


		Uint64 lastCounter = SDL_GetPerformanceCounter();

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

			Uint64 currentCounter = SDL_GetPerformanceCounter();
			double frameTime = (currentCounter - lastCounter) / frec;
			accumulatedTime += static_cast<float>(frameTime);
			lastCounter = currentCounter;

			while (accumulatedTime >= m_fixedDt)
			{
				accumulatedTime -= m_fixedDt;
				Tick(m_fixedDt);
			}

		}
	}


	void Application::Tick(float dt)
	{
		std::cout << "FPS is : " << 1.0f / dt << " \n";
	}

	void Application::Render()
	{

	}
}