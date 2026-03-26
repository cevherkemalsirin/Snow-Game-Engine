#pragma once
#include "Math/Vector2D.h"

class Line2D
{
	Vector2D pointStart_;
	Vector2D pointEnd_;

public:
	Line2D();
	Line2D(float x1, float y1, float x2, float y2);
	Line2D(const Vector2D& pointStart, const Vector2D& pointEnd);

	inline const Vector2D& GetPointStart() const { return pointStart_; }
	inline const Vector2D& GetPointEnd() const { return pointEnd_; }
	inline void SetPointStart(const Vector2D& pointStart) { pointStart_ = pointStart; }
	inline void SetPointEnd(const Vector2D& pointEnd) { pointEnd_ = pointEnd; }
	bool operator==(const Line2D& otherLine) const;

	Vector2D Midpoint() const;
	float Slope() const;
	float Length() const;
	void Rotate(float angle, const Vector2D & point);
	/*
		B *

   A -----D------- C

    if we create AB and AC vectors, and take dot product to find the shadow,
	end of the shadow(D) would be the closest point to the B.
	There are 2 approaches:
	1) A + AC * (AB*AC / |AC| * |AC|)
	2) A + Unit(AC) * ( AB * UNIT(AC))
	I will implement second approach
*/
	Vector2D ClosestPoint(const Vector2D& point, bool isSegment = true);
	float ClosestDistanceFrom(const Vector2D& point, bool isSegment = true);

};

