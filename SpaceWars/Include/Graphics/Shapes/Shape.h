#pragma once
#include <vector>
#include "Math/Vector2D.h"
#include <optional>


class Line2D;
class Rectangle2D;


class Shape
{
protected:
	std::vector<Vector2D> points_;

public:

	virtual Vector2D GetCenter() const = 0;
	inline virtual std::vector<Vector2D> GetPoints() const { return points_; }
	void MoveBy(const Vector2D& offset);
	virtual void MoveTo(const Vector2D& newPos) = 0;
	virtual std::optional<std::vector<Line2D>> GetLines() const = 0;
	virtual Rectangle2D GetBoundingBox() const = 0;
	virtual bool ContainsPoint(const Vector2D& point) const = 0;
	~Shape() {};

};

