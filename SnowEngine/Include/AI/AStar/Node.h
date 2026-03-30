#pragma once
#include <Graphics/Shapes/rectangle2D.h>

enum class NodeType : uint8_t
{
	Empty,
	Wall,
	Start,
	End,
	Open,
	Closed,
	Path
};

struct GridIndex
{
	int row{ 0 };
	int col{ 0 };
};


class Node
{
	//costs
	int costFromStart{ 0 }; //g cost
	//manatthan algorithm |x2-x1| + |y2-y1|
	int estimatedCostToEnd{ 0 }; //h cost
public:
	GridIndex gridLocation;
	GridIndex parentLocation{ -1,-1 };
	NodeType type;
	Rectangle2D cellRectangle;

	bool isInOpenList{ false };
	bool isInClosedList{ false };

	inline Node(int x, int y, const Rectangle2D& rect) :gridLocation{ x, y }, type{ NodeType::Empty }, cellRectangle{ rect } {}

	inline int gCost() const { return costFromStart; }
	inline int hCost() const { return estimatedCostToEnd; }
	inline int fCost() const { return costFromStart + estimatedCostToEnd; } //f cost

	inline void SetgCost(int cost) { costFromStart = cost; }
	inline void SethCost(int cost) { estimatedCostToEnd = cost; }

	inline bool isWalkable() const { return type != NodeType::Wall; }
};