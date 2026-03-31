#include "Framework/Application.h"
#include <SDL3/SDL.h>
#include  "Framework/World.h"
#include "Framework/Core.h"

namespace snw
{
	Application::Application(int width, int height, std::string_view appName) : m_running(true), m_targetFps(60.0f), m_fixedDt(1.0f / m_targetFps), m_screen(width, height, appName),m_width(width),m_height(height)
	{
		if (currentWorld)
		{
			currentWorld->BeginPlayInternal();
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
					snw::LOG("Key Down: {}", event.key.key);
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
				TickInternal(m_fixedDt);
			}
			RenderInternal();

		}
	}


	void Application::Tick(float dt)
	{

	}

	void Application::Render()
	{
		
	}

	void Application::TickInternal(float dt)
	{
		Tick(dt);
		if (currentWorld)
		{
			currentWorld->TickInternal(dt);
		}
	}

	void Application::RenderInternal()
	{
		m_screen.ClearScreen();
		
		Render();

		m_screen.Render();
	}
}