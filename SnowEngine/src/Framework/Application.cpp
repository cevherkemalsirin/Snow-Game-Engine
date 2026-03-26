#include "Framework/Application.h"
#include "Shapes/Rectangle2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/Circle2D.h"
#include <SDL3/SDL.h>
#include <iostream>
#include "Framework/Core.h"

namespace snw
{
	Application::Application(int width, int height, std::string_view appName) : m_running(true), m_targetFps(60.0f), m_fixedDt(1.0f / m_targetFps), m_screen(width, height, appName),m_width(width),m_height(height)
	{
		
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
		//snw::LOG("Fps is: {}", std::round(1.0f / dt));
	}

	void Application::Render()
	{
		
		Rectangle2D rect(Vector2D(0.f, 0.f), 50, 60);
		Circle2D circ(Vector2D(m_width / 2.f, m_height / 2.f), 100.f);
		Triangle2D trig(Vector2D(200.f, 1.f), Vector2D(100.f, 100.f), Vector2D(300.f, 100.f));
		m_screen.ShapeRenderer().DrawShape(&rect, Color::Green(), true);
		m_screen.ShapeRenderer().DrawShape(circ, Color::Red());
		m_screen.ShapeRenderer().DrawShape(&trig, Color::Orange(),true,Color::Orange(),true);
		
	}

	void Application::TickInternal(float dt)
	{
		Tick(dt);
	}

	void Application::RenderInternal()
	{
		m_screen.ClearScreen();
		
		Render();

		m_screen.Render();
	}
}