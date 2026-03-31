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

	inline bool operator == (const GridIndex& other) const
	{
		return row == other.row && col == other.col;
	}
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


	inline Node(int row, int col, const Rectangle2D& rect) :gridLocation{ row, col }, type{ NodeType::Empty }, cellRectangle{ rect } {}

	inline int gCost() const { return costFromStart; }
	inline int hCost() const { return estimatedCostToEnd; }
	inline int fCost() const { return costFromStart + estimatedCostToEnd; } //f cost

	inline void SetgCost(int cost) { costFromStart = cost; }
	inline void SethCost(int cost) { estimatedCostToEnd = cost; }

	inline bool isWalkable() const { return type != NodeType::Wall; }


	inline bool operator==(const Node& other) const
	{
		return this->gridLocation == other.gridLocation;
	}
	bool operator<(const Node& other) const
	{
		if (gridLocation.row != other.gridLocation.row)
			return gridLocation.row < other.gridLocation.row;
		return gridLocation.col < other.gridLocation.col;
	}
};