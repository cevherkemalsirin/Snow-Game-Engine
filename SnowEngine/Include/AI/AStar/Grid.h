#pragma once
#include "Node.h"
#include <Framework/Core.h>

class Grid
{
	snw::List<Node> m_grid;
	int m_cols;
	int m_rows;
	float m_cellWidth;
	float m_cellHeight;
	GridIndex m_startNodeIndex;
	GridIndex m_endNodeIndex;


	int GetNodeLinearIndex(int row, int column) const;
	void BuildGrid();
public:
	Grid(int colNumber, int rowNumber, float cellWidth, float cellHeight);

	

	inline int GetCols() const { return m_cols; }
	inline int GetRows() const { return m_rows; }
	inline float GetCellWidth() const { return m_cellWidth; }
	inline float GetCellHeight() const { return m_cellHeight; }

	bool isValidIndex(const GridIndex& index) const;
	bool isValidIndex(int row, int col) const { return isValidIndex({ row,col }); }
	
	Node& GetNode(int row, int col);
	const Node& GetNode(int row, int col) const;
	inline const GridIndex& GetStartNodeIndex() const { return m_startNodeIndex; }
	inline const GridIndex& GetEndNodeIndex() const { return m_endNodeIndex; }

	inline  Node& GetStartNode()  { return GetNode(m_startNodeIndex.row, m_startNodeIndex.col); }
	inline  Node& GetEndNode()  { return GetNode(m_endNodeIndex.row, m_endNodeIndex.col); }
	inline const Node& GetNode(const GridIndex& index) const { return GetNode(index.row, index.col); }
	inline  Node& GetNode(const GridIndex& index)  { return GetNode(index.row, index.col); }

	inline const snw::List<Node>& GetNodes() const { return m_grid; }

	void SetStartNode(int row, int col);
	void setEndNode(int row, int col);
	void setWallNode(int row, int col);

	void ResetGridData();
	

};