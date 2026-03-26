#include "Shapes/Shape.h"

void Shape::MoveBy(const Vector2D& offset)
{
	for (Vector2D& point : points_)
	{
		point += offset;
	}
}
