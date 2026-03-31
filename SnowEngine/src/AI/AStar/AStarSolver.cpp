#include "AI/AStar/AStarSolver.h"
#include <set>

bool AStarSolver::Solve(Grid& grid)
{
	snw::List<Node> openList;
	std::set<Node> closedList;

	 Node& startNode = grid.GetStartNode();
	startNode.SethCost(CalculateHeuristic(startNode, grid.GetEndNode()));
	startNode.SetgCost(0);
	openList.push_back(startNode);

	while (!openList.empty())
	{
		Node& currentNode = GetLowestFCostNode(grid, openList);
	
		if (currentNode == grid.GetEndNode())
		{
			ReconstructPath(grid);
			return true;
		}
		RemoveFromOpenList(openList, currentNode);
		closedList.insert(currentNode);
		if (currentNode.type != NodeType::Start &&
			currentNode.type != NodeType::End)
		{
			currentNode.type = NodeType::Closed;
		}

		snw::List<NeighborData> neighbors = GetNeighbors(grid, currentNode.gridLocation);

		for (const NeighborData& neighbor : neighbors)
		{
			Node& neighborNode = grid.GetNode(neighbor.index);
			if (!neighborNode.isWalkable() || closedList.find(neighborNode) != closedList.end())
			{
				continue;
			}
			const int totalCostFromStart = currentNode.gCost() + neighbor.moveCost;
			if (std::find(openList.begin(), openList.end(), neighborNode) == openList.end() || totalCostFromStart < neighborNode.gCost())
			{
				neighborNode.parentLocation = currentNode.gridLocation;
				neighborNode.SetgCost(totalCostFromStart);
				neighborNode.SethCost(CalculateHeuristic(neighborNode, grid.GetEndNode()));
				if (std::find(openList.begin(), openList.end(), neighborNode) == openList.end())
				{
					openList.push_back(neighborNode);
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

Node& AStarSolver::GetLowestFCostNode(const Grid& grid, snw::List<Node>& openList) 
{
	Node& lowestFCostNode = openList[0];
	for (auto& node : openList)
	{
		if(node.fCost() < lowestFCostNode.fCost())
		{
			lowestFCostNode = node;
		}
		else if (node.fCost() == lowestFCostNode.fCost() && node.hCost() < lowestFCostNode.hCost())
		{
			lowestFCostNode = node;
		}
	}
	return lowestFCostNode;
}

bool AStarSolver::RemoveFromOpenList(snw::List<Node>& openList, const Node& node)
{
	auto it = std::find(openList.begin(), openList.end(), node);
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
		Node& currentNode = grid.GetNode(currentIndex.row, currentIndex.col);

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
