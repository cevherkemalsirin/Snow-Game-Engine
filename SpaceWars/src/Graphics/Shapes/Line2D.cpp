#include "Shapes/Line2D.h"
#include "Math/Utils.h"

Line2D::Line2D(): Line2D(Vector2D::ZERO, Vector2D::ZERO)
{

}

Line2D::Line2D(float x1, float y1, float x2, float y2) :
	Line2D(Vector2D(x1, y1), Vector2D(x2, y2))
{

}

Line2D::Line2D(const Vector2D& pointStart, const Vector2D& pointEnd):
	pointStart_(pointStart), pointEnd_(pointEnd)
{

}

bool Line2D::operator==(const Line2D& otherLine) const
{
	return (pointStart_ == otherLine.GetPointStart()) && (pointEnd_ == otherLine.GetPointEnd());
}

Vector2D Line2D::Midpoint() const
{
	float midx = (pointStart_.GetX() + pointEnd_.GetX()) / 2.0f;
	float midy = (pointStart_.GetY() + pointEnd_.GetY()) / 2.0f;
	return Vector2D(midx, midy);
}

float Line2D::Slope() const
{
	float rise = pointEnd_.GetY() - pointStart_.GetY();
	float run = pointEnd_.GetX() - pointStart_.GetX();
	if (math::FEqualSmaller(run, 0.0f))
	{
		return 0.0f;
	}
	return rise / run;
}

float Line2D::Length() const
{
	return pointStart_.DistanceTo(pointEnd_);
}

void Line2D::Rotate(float angle, const Vector2D& point)
{
	pointStart_.RotateVector(angle, point);
	pointEnd_.RotateVector(angle, point);
}

Vector2D Line2D::ClosestPoint(const Vector2D& point, bool isSegment)
{
	Vector2D A = point - pointStart_;
	Vector2D B = pointEnd_ - pointStart_;

	//technnique 1)
	Vector2D Bunit = B.GetNormalized();
	float shadow = A.Dot(Bunit);
	if (isSegment) { 
		 shadow = std::max(0.0f, std::min(B.Magnitude(), shadow));
	}
	return pointStart_ + (shadow * Bunit);

	/*
	//tehnique 2)
	float l2 = B.Magnitude_square();
	float shadow2 = A.Dot(B) / l2;
	shadow2 = std::fmaxf(0.0f, std::fminf(1.0f, shadow2));
	return pointStart_ + (B * shadow2);
	*/
	
}

float Line2D::ClosestDistanceFrom(const Vector2D& point, bool isSegment)
{
	return point.DistanceTo(ClosestPoint(point, isSegment));
}

