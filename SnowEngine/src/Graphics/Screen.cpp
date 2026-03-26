#include "Screen.h"
#include <iostream>
#include "Framework/Core.h"
#include <SDL3/SDL.h>


Screen::Screen(int width, int height, std::string_view title) : m_width(width), m_height(height),m_screenBuffer(width,height), m_renderer2D(m_screenBuffer)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		snw::LOG("SDL failed to initialize");
		throw std::runtime_error("SDL initialization failed");
	}

	m_window = SDL_CreateWindow(title.data(), m_width, m_height, SDL_WINDOW_RESIZABLE);
	
	if (m_window == nullptr)
	{
		snw::LOG("Window creation failed");
		throw std::runtime_error("Window creation failed");
	}

	m_renderer = SDL_CreateRenderer(m_window,NULL);
	if (m_renderer == nullptr)
	{
		snw::LOG("Renderer creation failed");
		throw std::runtime_error("Renderer creation failed");
	}
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

	if (m_texture == nullptr)
	{
		throw std::runtime_error("Texture creation failed");
	}
}

void Screen::Render()
{
	SDL_UpdateTexture(m_texture, nullptr, m_screenBuffer.GetBuffer(), m_width * static_cast<int>(sizeof(m_screenBuffer.GetBuffer()[0])));
	SDL_RenderTexture(m_renderer, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_renderer);
}

void Screen::ClearScreen(const Color& color) 
{
	SDL_SetRenderDrawColor(m_renderer, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
	m_screenBuffer.Clear(color);
	SDL_RenderClear(m_renderer);
}

Screen::~Screen()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_DestroyTexture(m_texture);
	SDL_Quit();
}