#include "Renderer2D.h"
#include "ScreenBuffer.h"
#include "Math/Vector2D.h"
#include "Shapes/Line2D.h"
#include "Shapes/Shape.h"
#include "Shapes/Circle2D.h"
#include "Shapes/Rectangle2D.h"
#include "AI/AStar/Grid.h"


void Renderer2D::DrawPoint( int x, int y, Color color) const
{
	buffer.SetPixel(x, y, color);
}

void Renderer2D::DrawPoint(const Vector2D& point, Color color) const
{
	int x = static_cast<int>(point.GetX());
	int y = static_cast<int>(point.GetY());
	DrawPoint(x, y, color);
}

void Renderer2D::DrawLine(const Line2D& line, Color color) const
{
	float x = line.GetPointStart().GetX();
	float y = line.GetPointStart().GetY();
	float dx = std::roundf(line.GetPointEnd().GetX() - line.GetPointStart().GetX());
	float dy = std::roundf(line.GetPointEnd().GetY() - line.GetPointStart().GetY());

	int steps = static_cast<int>(std::max(std::fabs(dx), std::fabs(dy)));

	float xstep = dx / steps;
	float ystep = dy / steps;

	DrawPoint(x, y, color);
	for (int i = 1; i < steps; ++i)
	{
		x += xstep;
		y += ystep;
		DrawPoint(std::roundf(x), std::roundf(y), color);
	}
}

void Renderer2D::DrawShape(const Shape* shape, const Color& color, bool fill, const Color& fillColor, bool DrawBoundingBox) const
{
	if(!shape)
	{
		throw std::invalid_argument("Shape pointer cannot be null");
	}

	if (auto lines = shape->GetLines(); lines.has_value())
	{
		for (const auto& line : lines.value())
		{
			DrawLine(line, color);
		}

		if (fill)
		{
			Fill(shape, fillColor);
		}
		if (DrawBoundingBox)
		{
			Rectangle2D box = shape->GetBoundingBox();
			DrawShape(&box);
		}
	}
	else 
	{
		throw std::runtime_error("Shape does not have lines to draw");
	}
}

void Renderer2D::DrawShape(const Circle2D& circle, const Color& color, bool fill, const Color& fillColor, bool drawBoundingBox) const
{
	float x = 0;
	float r = circle.GetRadius();
	float y = r;
	float cx = circle.GetCenter().GetX();
	float cy = circle.GetCenter().GetY();
	

	while (x < y)
	{
		float midPoint = y - 0.5;
		if (x * x + midPoint * midPoint > r * r)
		{
			--y;
		}
		
		DrawPoint(Vector2D(cx + x,cy + y), color);
		DrawPoint(Vector2D(cx - x, cy + y), color);
		DrawPoint(Vector2D(cx + x, cy - y), color);
		DrawPoint(Vector2D(cx - x, cy - y), color);
		DrawPoint(Vector2D(cx + y, cy + x), color);
		DrawPoint(Vector2D(cx - y, cy + x), color);
		DrawPoint(Vector2D(cx + y, cy - x), color);
		DrawPoint(Vector2D(cx - y, cy - x), color);

		++x;
	}


	if (fill)
	{
		Fill(&circle, fillColor);
	}
	if (drawBoundingBox)
	{
		Rectangle2D  box = circle.GetBoundingBox();
		DrawShape(&box);
	}

}



void Renderer2D::Fill(const Shape* shape, const Color& color)const
{
	if (!shape)
	{
		throw std::invalid_argument("Shape pointer cannot be null");
	}

	Rectangle2D  box = shape->GetBoundingBox();
	int rowStart = static_cast<int>(box.GetTopLeftPoint().GetY());
	int rowEnd = static_cast<int>(box.GetBottomRightPoint().GetY());
	int colStart = static_cast<int>(box.GetTopLeftPoint().GetX());
	int colEnd = static_cast<int>(box.GetBottomRightPoint().GetX());
	for (int y = rowStart; y < rowEnd; ++y)
	{
		for (int x = colStart; x < colEnd; ++x)
		{
			Vector2D currentPoint(x, y);
			if (shape->ContainsPoint(currentPoint))
			{
				DrawPoint(currentPoint, color);
			}
		}
	}
	
}

void Renderer2D::DrawGrid(const Grid& grid) const
{
	for (const auto& node : grid.GetNodes())
	{
		Color fillColor;
		Color borderColor = Color::Black();
		switch (node.type)
		{
		case NodeType::Empty:
			fillColor = Color::White();
			break;
		case NodeType::Wall:
			fillColor = Color::Black();
			break;
		case NodeType::Start:
			fillColor = Color::Green();
			break;
		case NodeType::End:
			fillColor = Color::Orange();
			break;
		case NodeType::Open:
			fillColor = Color::Blue();
			break;
		case NodeType::Closed:
			fillColor = Color::Red();
			break;
		case NodeType::Path:
			fillColor = Color::Yellow();
			break;
		default:
			fillColor = Color::White();
			break;
		}
		DrawShape(&node.cellRectangle, borderColor, true, fillColor);
	}
}
