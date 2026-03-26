#pragma once
#include "Shape.h"


class Triangle2D : public Shape
{
	
public:
	Triangle2D();
	Triangle2D(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2);

	inline void SetP0(const Vector2D& p0) { GetPoints()[0] = p0; }
	inline void SetP1(const Vector2D& p1) { GetPoints()[1] = p1; }
	inline void SetP2(const Vector2D& p2) { GetPoints()[2] = p2; }

	inline  Vector2D GetP0() const { return GetPoints()[0]; }
	inline  Vector2D GetP1() const { return GetPoints()[1]; }
	inline  Vector2D GetP2() const { return GetPoints()[2]; }

	virtual std::optional<std::vector<Line2D>> GetLines() const override;

	virtual Vector2D GetCenter() const override;
	virtual Rectangle2D GetBoundingBox() const override;
	//move the triangle to a new position by centering it at the new position
	virtual void MoveTo(const Vector2D& newPos) override;

	float Area() const;
	/*
	* if it is inside of the triangle then dividing the triangle into a 3 smaller triangle with this point and
	* if area sum of these triangles are equal to the big triangle then it is inside of the shape
	*/
	virtual bool ContainsPoint(const Vector2D& point) const override;

private:
	float Area(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2) const;
};

