#include "AI/AStar/Grid.h"


Grid::Grid(int cols, int rows, float cellWidth, float cellHeight)
	:m_cols(cols), m_rows(rows), m_cellWidth(cellWidth), m_cellHeight(cellHeight)
{
	m_startNodeIndex = { -1, -1 };
	m_endNodeIndex = { -1,-1 };
	BuildGrid();
}

int Grid::GetNodeLinearIndex(int row, int column) const
{
	return (row * m_cols) + column;
}


 bool Grid::isValidIndex(const GridIndex& index) const
{
	int row = index.row;
	int col = index.col;
	if(row < 0 || row >= m_rows || col < 0 || col >= m_cols)
	{
		return false;
	}
	return true;
}

Node& Grid::GetNode(int row, int col)
{
	if (!isValidIndex({ row, col }))
	{
		throw std::out_of_range("Invalid grid index");
	}
	return m_grid[GetNodeLinearIndex(row, col)];
}

const Node& Grid::GetNode(int row, int col) const
{
	if (!isValidIndex({row, col}))
	{		
		throw std::out_of_range("Invalid grid index");
	}
	return m_grid[GetNodeLinearIndex(row, col)];
}

void Grid::SetStartNode(int row, int col)
{
	if (!isValidIndex({row, col}))
	{
		throw std::out_of_range("Invalid grid index");
	}

	if (isValidIndex(GridIndex(m_endNodeIndex.row, m_endNodeIndex.col)))
	{
		Node& previousStartNode = GetNode(m_startNodeIndex.row, m_startNodeIndex.col);
		if (previousStartNode.isWalkable())
		{
			previousStartNode.type = NodeType::Empty;
		}
	}

	Node& node = GetNode(row, col);
	node.type = NodeType::Start;
	node.parentLocation = { -1, -1 };
	m_startNodeIndex = { row, col };
}

void Grid::setEndNode(int row, int col)
{
	if (!isValidIndex({ row, col }))
	{
		throw std::out_of_range("Invalid grid index");
	}

	Node& node = GetNode(row, col);
	//if there is already an end node then we need to reset it
	if (isValidIndex(GridIndex(m_endNodeIndex.row, m_endNodeIndex.col)))
	{
		Node& prevEndNode = GetNode(m_endNodeIndex.row, m_endNodeIndex.col);
		if (prevEndNode.isWalkable())
		{
			prevEndNode.type = NodeType::Empty;
			node.parentLocation = prevEndNode.parentLocation;
			prevEndNode.parentLocation = { -1, -1 };
		}
	}

	node.type = NodeType::End;
	m_endNodeIndex = { row, col };
}

void Grid::setWallNode(int row, int col)
{
	if (!isValidIndex({ row, col }))
	{
		throw std::out_of_range("Invalid grid index");
	}
	Node& node = GetNode(row, col);
	if (node.type == NodeType::Start || node.type == NodeType::End)
	{
		throw std::invalid_argument("Cannot set a wall on the start or end node");
	}
	node.type = NodeType::Wall;
}

void Grid::BuildGrid()
{
	m_grid.clear();
	m_grid.reserve(m_rows * m_cols);
	
	for (int r = 0; r < m_rows; ++r)
	{
		for (int c = 0; c < m_cols; ++c)
		{
			const float x = static_cast<float>(c) * m_cellWidth;
			const float y = static_cast<float>(r) * m_cellHeight;

			Vector2D topLeft(x, y);
			Rectangle2D cellRectangle(topLeft, m_cellWidth, m_cellHeight);
			Node newNode(r, c, cellRectangle);
			m_grid.push_back(newNode);
		}
	}
}

void Grid::ResetGridData()
{
	for (auto& node : m_grid)
	{
		node.SetgCost(0);
		node.SethCost(0);
		node.parentLocation = { -1, -1 };
		if (node.type == NodeType::Open || node.type == NodeType::Closed || node.type == NodeType::Path)
		{
			node.type = NodeType::Empty;
		}
	}
}

