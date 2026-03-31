#pragma once
#include "Grid.h"

struct NeighborData
{
	int moveCost{ 10 };
	GridIndex index;
};

class AStarSolver {

public:
	bool Solve(Grid& grid);
private:
	//Octile distance min(dx,dy) * 14 + |dx-dy| * 10
	int CalculateHeuristic(const Node& startNode, const Node& endNode)const;
	snw::List<NeighborData> GetNeighbors(const Grid& grid, const GridIndex& current)const;
	Node& GetLowestFCostNode(const Grid& grid,  snw::List<Node>& openList);
	bool RemoveFromOpenList(snw::List<Node>& openList, const Node& node);
	void ReconstructPath(Grid& grid);
};