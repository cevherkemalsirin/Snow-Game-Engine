#pragma once

#include "Shapes/Line2D.h"
#include "Shapes/Rectangle2D.h"


/*
*      ^  normal
       |
---------------- edge

*/


enum class EdgeType {
	BOTTOM_EDGE=0,
	TOP_EDGE,
	LEFT_EDGE,
	RIGHT_EDGE,
	NUM_EDGES
};

static const Vector2D UP_DIR = { 0, -1 };
static const Vector2D DOWN_DIR = { 0,1 };
static const Vector2D LEFT_DIR = { -1,0 };
static const Vector2D RIGTH_DIR = { 1,0 };

struct BoundaryEdge {
	Vector2D normal;
	Line2D edge;
};