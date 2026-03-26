#pragma once
#include "Shape.h"


class Circle2D : public Shape
{
	float radius_;

public:
	Circle2D():Circle2D(Vector2D::ZERO, 0.0f){}
	Circle2D(const Vector2D& center, float r);

	inline  Vector2D GetCenter() const { return points_[0]; };
	inline void SetCenter(const Vector2D center) { points_[0] = center; }
	inline float GetRadius() const { return radius_; }
	inline void SetRadius(float r) { radius_ = r; }

	virtual Rectangle2D GetBoundingBox() const override;
	virtual void MoveTo(const Vector2D& newPos) override;
	std::optional <std::vector<Line2D>> GetLines() const override;
	virtual bool ContainsPoint(const Vector2D& point) const override;

	bool Intersect(const Circle2D& otherCircle) const;
	
};

