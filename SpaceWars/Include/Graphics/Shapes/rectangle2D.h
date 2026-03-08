#pragma once
#include "Shape.h"

class Line2D;

class Rectangle2D : public Shape
{

public:
	Rectangle2D();
	Rectangle2D(const Vector2D& topLeftP, const Vector2D& bottomRightP);
	Rectangle2D(const Vector2D& topLeftP, unsigned int height, unsigned int width);

	inline void SetTopLeftPoint(const Vector2D& topLeft) { points_[0] = topLeft; }
	inline void SetBottomRightPoint(const Vector2D& bottomRight) { points_[2] = bottomRight; }

	inline Vector2D GetTopLeftPoint() const { return points_[0]; }
	inline Vector2D GetBottomRightPoint() const { return points_[2]; }

	virtual Vector2D GetCenter() const override;
	virtual Rectangle2D GetBoundingBox() const override;

	float GetHeight() const;
	float GetWidth() const;
	virtual std::optional<std::vector<Line2D>> GetLines() const override;
	float Area() const;


	bool Intersects(const Rectangle2D& targetRect) const;
	virtual bool ContainsPoint(const Vector2D & point) const override;
	void MoveTo(const Vector2D& targetPosition);

	static Rectangle2D Inset(const Rectangle2D& rect, const Vector2D& insetOffset);


};

