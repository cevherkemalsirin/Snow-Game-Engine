#include "Framework/Application.h"
#include <SDL3/SDL.h>
#include  "Framework/World.h"
#include "Framework/Core.h"

namespace snw
{
	Application::Application(int width, int height, std::string_view appName) : m_running(true), m_targetFps(60.0f), m_fixedDt(1.0f / m_targetFps), m_screen(width, height, appName), m_width(width), m_height(height), m_inputController([this](float dt, InputState) { m_running = false;})
	{
	
		if (currentWorld)
		{
			currentWorld->BeginPlayInternal();
		}
	}

	void Application::Run()
	{
		float accumulatedTime = 0.0f;
		double freq = static_cast<double>(SDL_GetPerformanceFrequency());

		Uint64 lastCounter = SDL_GetPerformanceCounter();

		while (m_running)
		{
			Uint64 currentCounter = SDL_GetPerformanceCounter();
			double frameTime = static_cast<double>(currentCounter - lastCounter) / freq;
			lastCounter = currentCounter;

			// Optional safety clamp, prevents huge jump after breakpoint/window drag
			if (frameTime > 0.25)
			{
				frameTime = 0.25;
			}

			accumulatedTime += static_cast<float>(frameTime);

			m_inputController.Tick(m_fixedDt);

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