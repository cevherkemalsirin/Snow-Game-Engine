
#pragma once
#include <stdint.h>

struct SDL_PixelFormatDetails;

class Color
{
	uint32_t m_color;
	static const SDL_PixelFormatDetails* m_format;
public:
	Color() :Color(0) {};
	explicit Color(uint32_t color) : m_color(color) {};
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	inline bool operator==(const Color& color)const { return m_color == color.m_color; }
	inline bool operator!=(const Color& color)const { return !(*this == color); }

	void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	inline static void InitFormat(SDL_PixelFormatDetails* format) { m_format = format; }

	//static Color AlphaBlend(const Color& newColor, const Color& currentColor);

	void SetRed(uint8_t red);
	void SetGreen(uint8_t green);
	void SetBlue(uint8_t blue);
	void SetAlpha(uint8_t alpha);

	inline uint32_t GetPixelColor() const { return m_color; }
	uint8_t GetRed() const;
	uint8_t GetGreen() const;
	uint8_t GetBlue() const;
	uint8_t GetAlpha() const;

	static Color Black() { return Color(0, 0, 0, 255); }
	static Color White() { return Color(255, 255, 255, 255); }
	static Color Blue() { return Color(0, 0, 255, 255); }
	static Color Red() { return Color(255, 0, 0, 255); }
	static Color Green() { return Color(0, 255, 0, 255); }
	static Color Yellow() { return Color(255, 255, 0, 255); }
	static Color Purple() { return Color(255, 0, 255, 255); }
	static Color Cyan() { return Color(37, 240, 217, 255); }
	static Color Pink() { return Color(205, 128, 213, 255); }
	static Color Orange() { return Color(255, 102, 0, 255); }
};



