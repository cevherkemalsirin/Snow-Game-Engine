#include "Shapes/Triangle.h"
#include "Shapes/rectangle2D.h"
#include "Shapes/Line2D.h"
#include "Math/Utils.h"

Triangle2D::Triangle2D():Triangle2D(Vector2D::ZERO, Vector2D::ZERO, Vector2D::ZERO)
{
}

Triangle2D::Triangle2D(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2)
{
	points_.push_back(p0);
	points_.push_back(p1);
	points_.push_back(p2);
}

std::optional<std::vector<Line2D>> Triangle2D::GetLines() const
{
	Line2D line1(GetP0(), GetP1());
	Line2D line2(GetP1(), GetP2());
	Line2D line3(GetP2(), GetP0());
	return std::vector<Line2D>{line1,line2,line3};
}

Vector2D Triangle2D::GetCenter() const
{
	float midX = (GetP0().GetX() + GetP1().GetX() + GetP2().GetX()) / 3.0f;
	float midY = (GetP0().GetY() + GetP1().GetY() + GetP2().GetY()) / 3.0f;
	return Vector2D(midX, midY);
}

Rectangle2D Triangle2D::GetBoundingBox() const
{
	//top left of bounding box
	float topx = fmin(GetP0().GetX(), fmin(GetP1().GetX(), GetP2().GetX()));
	float topy = fmin(GetP0().GetY(), fmin(GetP1().GetY(), GetP2().GetY()));
	//bottom right bounding box
	float botx = fmax(GetP0().GetX(), fmax(GetP1().GetX(), GetP2().GetX()));
	float boty = fmax(GetP0().GetY(), fmax(GetP1().GetY(), GetP2().GetY()));
	return Rectangle2D(Vector2D(topx, topy), Vector2D(botx, boty));
}

void Triangle2D::MoveTo(const Vector2D& newPos)
{
	Vector2D moveOffset = newPos - GetCenter();
	MoveBy(moveOffset);
}

float Triangle2D::Area() const
{
	return Area(GetP0(), GetP1(), GetP2());
}

bool Triangle2D::ContainsPoint(const Vector2D& p) const
{
	float area1 = Area(GetP0(), GetP1(), p);
	float area2 = Area(GetP1(), GetP2(), p);
	float area3 = Area(GetP2(), GetP0(), p);
	return math::FEqual((area1 + area2 + area3), Area());
}

float Triangle2D::Area(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2) const
{
	float area = (p0.GetX() * (p1.GetY() - p2.GetY()) +
		p1.GetX() * (p2.GetY() - p0.GetY()) +
		p2.GetX() * (p0.GetY() - p1.GetY())) / 2.0f;
	return fabs(area);
}
