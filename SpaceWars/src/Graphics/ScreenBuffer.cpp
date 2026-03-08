#include "Graphics/ScreenBuffer.h"

void ScreenBuffer::SetPixel(int x, int y, Color color)
{
	if (x < m_width && y < m_height)
	{
		m_buffer[y * m_width + x] = color.GetPixelColor();
	}
}

Color ScreenBuffer::GetPixel(int x, int y) const
{
	if (x < m_width && y < m_height)
	{
		return Color(m_buffer[y * m_width + x]);
	}
	return Color::Black();
}

void ScreenBuffer::Clear(const Color& color)
{
	std::fill(m_buffer.begin(), m_buffer.end(), color.GetPixelColor());
}