#include "Shapes/Rectangle2D.h"
#include "Shapes/Line2D.h"

Rectangle2D::Rectangle2D():Rectangle2D(Vector2D::ZERO, Vector2D::ZERO)
{
	
}

Rectangle2D::Rectangle2D(const Vector2D& startP, const Vector2D& endP)
{
	points_.push_back(startP);
	points_.push_back(Vector2D(endP.GetX(), startP.GetY()));
	points_.push_back(endP);
	points_.push_back(Vector2D(startP.GetX(), endP.GetY()));
}

Rectangle2D::Rectangle2D(const Vector2D& topLeftP, unsigned int height, unsigned int width)
{
	Vector2D bottomRightP = Vector2D(topLeftP.GetX() + width - 1, topLeftP.GetY() + height - 1);
	*this = Rectangle2D(topLeftP, bottomRightP);
}

Vector2D Rectangle2D::GetCenter() const
{
	float midx = (GetTopLeftPoint().GetX() + GetBottomRightPoint().GetX()) / 2.0f;
	float midy = (GetBottomRightPoint().GetY() + GetTopLeftPoint().GetY()) / 2.0f;
	return Vector2D(midx, midy);
}

Rectangle2D Rectangle2D::GetBoundingBox() const
{
	return *this;
}


float Rectangle2D::GetHeight() const
{
	return GetBottomRightPoint().GetY() - GetTopLeftPoint().GetY() + 1;
}

float Rectangle2D::GetWidth() const
{
	return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX() + 1;
}

std::optional<std::vector<Line2D>> Rectangle2D::GetLines() const
{
	Line2D line1(GetPoints()[0], GetPoints()[1]);
	Line2D line2(GetPoints()[1], GetPoints()[2]);
	Line2D line3(GetPoints()[2], GetPoints()[3]);
	Line2D line4(GetPoints()[3], GetPoints()[0]);
	return std::vector<Line2D>{line1, line2, line3, line4};
}

float Rectangle2D::Area() const
{
	return GetHeight() * GetWidth();
}

bool Rectangle2D::Intersects(const Rectangle2D& targetRect) const
{
	return !(targetRect.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX()
		|| targetRect.GetBottomRightPoint().GetY() < GetTopLeftPoint().GetY()
        || targetRect.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX()
		|| targetRect.GetTopLeftPoint().GetY() > GetBottomRightPoint().GetY());
}

bool Rectangle2D::ContainsPoint(const Vector2D& point) const
{
	bool withinX = (point.GetX() < GetBottomRightPoint().GetX() && point.GetX() > GetTopLeftPoint().GetX());
	bool withinY = (point.GetY() < GetBottomRightPoint().GetY() && point.GetY() > GetTopLeftPoint().GetY());

	return (withinX && withinY);
}

void Rectangle2D::MoveTo(const Vector2D& targetPosition)
{
	//take height and width first since they will be give wrong values if we get them after
	//setting up the top left point of the rectangle
	float height = GetHeight();
	float width = GetWidth();
	SetTopLeftPoint(targetPosition);
	SetBottomRightPoint(Vector2D(GetTopLeftPoint().GetX() + width - 1, GetTopLeftPoint().GetY() + height - 1));
}

Rectangle2D Rectangle2D::Inset(const Rectangle2D& rect, const Vector2D& insetOffset)
{
	Vector2D newTopLeftP = rect.GetTopLeftPoint() + insetOffset;
	Vector2D newBottomRightP = rect.GetBottomRightPoint() - insetOffset;
	return Rectangle2D(newTopLeftP,newBottomRightP);
}
