#pragma once
#include "Renderer2D.h"
#include "ScreenBuffer.h"
#include <string_view>

class SDL_Texture;
class SDL_Renderer;
class SDL_Window;


class Screen
{
private:
	//customs
	Renderer2D m_renderer2D;
	ScreenBuffer m_screenBuffer;
	//SDL
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;


	int m_width;
	int m_height;

public:
	Screen(int width, int height, std::string_view title);
	~Screen();

	void Render();
	void ClearScreen(const Color& color = Color::Black());
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	const Renderer2D& ShapeRenderer() const { return m_renderer2D; }
};