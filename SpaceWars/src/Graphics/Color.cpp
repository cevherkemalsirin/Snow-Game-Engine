#include "Graphics/Color.h"
#include <SDL3/SDL.h>


const SDL_PixelFormatDetails* Color::m_format = nullptr;

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
		m_color = (a << 24) | (r << 16) | (g << 8) | b;
}


void Color::SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	if (!m_format)
	{
		m_format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	}

	m_color = SDL_MapRGBA(m_format, nullptr, r, g, b, a);
}

void Color::SetRed(uint8_t red)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	SDL_GetRGBA(m_color, m_format, nullptr ,&r,&g, &b, &a);
	SetRGBA(red, g, b, a);
}

void Color::SetGreen(uint8_t green)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	SDL_GetRGBA(m_color, m_format, nullptr, &r, &g, &b, &a);
	SetRGBA(r, green, b, a);
}

void Color::SetBlue(uint8_t blue)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	SDL_GetRGBA(m_color, m_format, nullptr, &r, &g, &b, &a);
	SetRGBA(r, g, blue, a);
}

void Color::SetAlpha(uint8_t alpha)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	SDL_GetRGBA(m_color, m_format, nullptr, &r, &g, &b, &a);
	SetRGBA(r, g, b, alpha);
}

uint8_t Color::GetRed() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	SDL_GetRGBA(m_color, m_format, nullptr, &r, &g, &b, &a);
	return r;
}

uint8_t Color::GetBlue() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	SDL_GetRGBA(m_color, m_format, nullptr, &r, &g, &b, &a);
	return b;
}

uint8_t Color::GetAlpha() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	SDL_GetRGBA(m_color, m_format, nullptr, &r, &g, &b, &a);
	return a;
}

uint8_t Color::GetGreen() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	SDL_GetRGBA(m_color, m_format, nullptr, &r, &g, &b, &a);
	return g;
}