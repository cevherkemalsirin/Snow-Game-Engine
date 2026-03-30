
#pragma once
#include <stdint.h>
#include "Color.h"

class ScreenBuffer;
class Line2D;
class Circle2D;
class Shape;
class Vector2D;
class Grid;

class Renderer2D
{
private:
	ScreenBuffer& buffer;

	void Fill(const Shape* shape, const Color& color = Color::White())const;
public:
	Renderer2D(ScreenBuffer& buffer) :buffer{buffer} {}

	void DrawPoint(int x, int y, Color color = Color::White())const;
	void DrawPoint(const Vector2D& point, Color color = Color::White())const;
	//Implemented using DDA algorithm more info at https://www.youtube.com/watch?v=W5P8GlaEOSI
	void DrawLine(const Line2D& line, Color color = Color::White())const;

	/*Draw any 2D shape Rectangle2D, circle2D, Triangle2D, Star2D In order to draw
	  a line see DrawLine()

	  @param shape: shape to draw
	  @param color: color of the shape
	  @param fill: if true then it will fill the shape with fillColor
	  @param fillColor: color to fill the shape with if fill is true
	  @param drawBoundingBox: if true then it will draw the bounding box of the shape. Bounding box of rectangle is itself, bounding box of triangle is the smallest rectangle that can contain the triangle and bounding box of circle is the smallest square that can contain the circle etc.
	  */
	void DrawShape(const Shape* shape, const Color& color = Color::White(), bool fill = false, const Color& fillColor = Color::White(), bool DrawBoundingBox = false) const;

	/*
	* Mid point circle algorithm
	https://www.youtube.com/watch?v=hpiILbMkF9w
	*/

	void DrawShape(const Circle2D& circle, const Color& color = Color::White(), bool fill = false, const Color& fillColor = Color::White(), bool drawBoundingBox = false) const;

	/*
	* Draw Grid for A* pathfinding algorithm
	*/
	void DrawGrid(const Grid& grid) const;
};