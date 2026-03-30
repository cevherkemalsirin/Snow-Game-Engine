#pragma once
#include <vector>
#include "Node.h"
#include <Framework/Core.h>

class Grid
{
	snw::List<snw::List<Node>> grid;
public:
	Vector2D gridWorldSize;
	float nodeRadius;
};