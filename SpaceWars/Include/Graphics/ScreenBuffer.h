#include "Color.h"
#include <vector>

class ScreenBuffer
{
	std::vector<uint32_t> m_buffer;
	uint16_t m_width;
	uint16_t m_height;

public:
		ScreenBuffer(uint16_t width, uint16_t height) : m_width(width), m_height(height), m_buffer(width * height) {}
		
		void SetPixel(uint16_t x, uint16_t y, const Color& color);
		Color GetPixel(uint16_t x, uint16_t y) const;

		uint32_t* GetBuffer() { return m_buffer.data(); }
		void Clear(const Color& color = Color::Black());
};