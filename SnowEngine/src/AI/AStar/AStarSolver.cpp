#include "AI/AStar/AStarSolver.h"
#include <set>

bool AStarSolver::Solve(Grid& grid)
{
	snw::List<GridIndex> openList;
	std::set<GridIndex> closedList;

	 Node& startNode = grid.GetStartNode();
	startNode.SethCost(CalculateHeuristic(startNode, grid.GetEndNode()));
	startNode.SetgCost(0);
	startNode.parentLocation = { -1, -1 };
	openList.push_back(startNode.gridLocation);

	while (!openList.empty())
	{
		GridIndex currentIndex = GetLowestFCostNode(grid, openList);
		Node& currentNode = grid.GetNode(currentIndex);

		if (currentIndex == grid.GetEndNodeIndex())
		{
			ReconstructPath(grid);
			return true;
		}
		RemoveFromOpenList(openList, currentIndex);
		closedList.insert(currentIndex);
		if (currentNode.type != NodeType::Start &&
			currentNode.type != NodeType::End)
		{
			currentNode.type = NodeType::Closed;
		}

		snw::List<NeighborData> neighbors = GetNeighbors(grid,currentIndex);

		for (const NeighborData& neighbor : neighbors)
		{
			Node& neighborNode = grid.GetNode(neighbor.index);
			if (!neighborNode.isWalkable() || closedList.find(neighbor.index) != closedList.end())
			{
				continue;
			}
			const int totalCostFromStart = currentNode.gCost() + neighbor.moveCost;

			if (std::find(openList.begin(), openList.end(), neighbor.index) == openList.end() || totalCostFromStart < neighborNode.gCost())
			{
				neighborNode.parentLocation = currentIndex;
				neighborNode.SetgCost(totalCostFromStart);
				neighborNode.SethCost(CalculateHeuristic(neighborNode, grid.GetEndNode()));

				if (std::find(openList.begin(), openList.end(), neighbor.index) == openList.end())
				{
					openList.push_back(neighbor.index);

					if (neighborNode.type != NodeType::Start &&
						neighborNode.type != NodeType::End)
					{
						neighborNode.type = NodeType::Open;
					}
				}
			}
		}
	}
	return false;
}

int AStarSolver::CalculateHeuristic(const Node& startNode, const Node& endNode) const
{
	int dx = std::abs(startNode.gridLocation.col - endNode.gridLocation.col);
	int dy = std::abs(startNode.gridLocation.row - endNode.gridLocation.row);
	return std::min(dx, dy) * 14 + std::abs(dx-dy) * 10;	
}

snw::List<NeighborData> AStarSolver::GetNeighbors(const Grid& grid, const GridIndex& current) const
{
	snw::List<NeighborData> neighbors;
	const GridIndex up{ current.row - 1, current.col };
	const GridIndex down{ current.row + 1, current.col };
	const GridIndex left{ current.row, current.col - 1 };
	const GridIndex right{ current.row, current.col + 1 };
	const GridIndex upLeft{ current.row - 1, current.col - 1 };
	const GridIndex upRight{ current.row - 1, current.col + 1 };
	const GridIndex downLeft{ current.row + 1, current.col - 1 };
	const GridIndex downRight{ current.row + 1, current.col + 1 };

	if(grid.isValidIndex(up) && grid.GetNode(up).isWalkable())
	{
		neighbors.push_back({ 10, up });
	}
	if(grid.isValidIndex(down) && grid.GetNode(down).isWalkable())
	{
		neighbors.push_back({ 10, down });
	}
	if(grid.isValidIndex(left) && grid.GetNode(left).isWalkable())
	{
		neighbors.push_back({ 10, left });
	}
	if(grid.isValidIndex(right) && grid.GetNode(right).isWalkable())
	{
		neighbors.push_back({ 10, right });
	}
	if(grid.isValidIndex(upLeft) && grid.GetNode(upLeft).isWalkable())
	{
		neighbors.push_back({ 14, upLeft });
	}
	if(grid.isValidIndex(upRight) && grid.GetNode(upRight).isWalkable())
	{
		neighbors.push_back({ 14, upRight });
	}
	if(grid.isValidIndex(downLeft) && grid.GetNode(downLeft).isWalkable())
	{
		neighbors.push_back({ 14, downLeft });
	}
	if(grid.isValidIndex(downRight) && grid.GetNode(downRight).isWalkable())
	{
		neighbors.push_back({ 14, downRight });
	}

	return neighbors;
}

GridIndex AStarSolver::GetLowestFCostNode(const Grid& grid, snw::List<GridIndex>& openList)
{
	GridIndex bestIndex = openList[0];
	const Node& bestNodeInitial = grid.GetNode(bestIndex);
	int bestFCost = bestNodeInitial.fCost();
	int bestHCost = bestNodeInitial.hCost();


	for (size_t i = 1; i < openList.size(); ++i)
	{
		const GridIndex& currentIndex = openList[i];
		const Node& currentNode = grid.GetNode(currentIndex);

		if (currentNode.fCost() < bestFCost ||
			(currentNode.fCost() == bestFCost && currentNode.hCost() < bestHCost))
		{
			bestIndex = currentIndex;
			bestFCost = currentNode.fCost();
			bestHCost = currentNode.hCost();
		}
	}

	return bestIndex;
}

bool AStarSolver::RemoveFromOpenList(snw::List<GridIndex>& openList, const GridIndex& index)
{
	auto it = std::find(openList.begin(), openList.end(), index);
	if (it != openList.end())
	{
		openList.erase(it);
		return true;
	}
	return false;
}

void AStarSolver::ReconstructPath(Grid& grid)
{
	const GridIndex startIndex = grid.GetStartNodeIndex();
	GridIndex currentIndex = grid.GetEndNodeIndex();

	while (currentIndex != startIndex)
	{
		Node& currentNode = grid.GetNode(currentIndex);

		if (currentNode.type != NodeType::Start &&
			currentNode.type != NodeType::End)
		{
			currentNode.type = NodeType::Path;
		}

		if (currentNode.parentLocation.row == -1 || currentNode.parentLocation.col == -1)
		{
			break;
		}

		currentIndex = currentNode.parentLocation;
	}
}
