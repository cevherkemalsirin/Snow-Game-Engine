#include "Color.h"
#include <vector>

class ScreenBuffer
{
private:
	std::vector<uint32_t> m_buffer;
	int m_width;
	int m_height;

public:
		ScreenBuffer(int width, int height) : m_width(width), m_height(height), m_buffer(width * height) {}
		
		void SetPixel(int x, int y, Color color);
		Color GetPixel(int x, int y) const;

		uint32_t* GetBuffer() { return m_buffer.data(); }
		void Clear(const Color& color = Color::Black());
};