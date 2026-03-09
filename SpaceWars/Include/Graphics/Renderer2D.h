
#pragma once
#include <stdint.h>
#include "Color.h"

class ScreenBuffer;
class Line2D;
class Circle2D;
class Shape;
class Vector2D;

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

	/*@param drawingAngle : max possible value : 360
	 if drawing angle is 10 degree then there will be 36 points to draw the circle. If drawing angle is 1 degree then there will be 360 points to draw the circle. So smaller the drawing angle more smoother the circle will be but it will impact performance. Negative or extreme values will be treated as 360 degrees.*/

	void DrawShape(const Circle2D& circle, float drawingAngle, const Color& color = Color::White(), bool fill = false, const Color& fillColor = Color::White(), bool drawBoundingBox = false) const;
};