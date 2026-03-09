#include "Renderer2D.h"
#include "ScreenBuffer.h"
#include "Math/Vector2D.h"
#include "Shapes/Line2D.h"
#include "Shapes/Shape.h"
#include "Shapes/Circle2D.h"
#include "Shapes/Rectangle2D.h"


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

void Renderer2D::DrawShape(const Circle2D& circle, float drawingAngle, const Color& color, bool fill, const Color& fillColor, bool drawBoundingBox) const
{
	if (drawingAngle <= 0.0f || drawingAngle >= 360.0f)
	{
		drawingAngle = 360.0f;
	}

	float fullDegree = 360.0f;
	float quarterDegree = fullDegree / 4.0f;
	Vector2D rightEnd(circle.GetCenter().GetX() + circle.GetRadius(), circle.GetCenter().GetY());
	Vector2D topEnd(circle.GetCenter().GetX(), circle.GetCenter().GetY() - circle.GetRadius());
	Vector2D leftEnd(circle.GetCenter().GetX() - circle.GetRadius(), circle.GetCenter().GetY());
	Vector2D bottomEnd(circle.GetCenter().GetX(), circle.GetCenter().GetY() + circle.GetRadius());
	for (float i = 0.0f; i < quarterDegree; i += drawingAngle / fullDegree)
	{
		rightEnd.RotateVector(drawingAngle, circle.GetCenter());
		topEnd.RotateVector(drawingAngle, circle.GetCenter());
		leftEnd.RotateVector(drawingAngle, circle.GetCenter());
		bottomEnd.RotateVector(drawingAngle, circle.GetCenter());
		DrawPoint(rightEnd, color);
		DrawPoint(topEnd, color);
		DrawPoint(leftEnd, color);
		DrawPoint(bottomEnd, color);
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
