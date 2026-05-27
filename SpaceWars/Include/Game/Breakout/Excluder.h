#pragma once

#include "Graphics/Shapes/Rectangle2D.h"
#include "BoundaryEdge.h"

class Excluder
{
public:
	virtual ~Excluder() {};

	void Init(const Rectangle2D& rect, bool reverseNormals = false);
	bool HasCollided(const Rectangle2D& rect, BoundaryEdge& edge) const;
	Vector2D GetCollisionOffset(const Rectangle2D& rect) const;
	inline Rectangle2D& GetRectangle()  { return m_rect; }
	void MoveBy(const Vector2D& delta);
	void MoveToPoint(const Vector2D& point);
	const BoundaryEdge& GetEdge(EdgeType edge) const;

private:
	Rectangle2D m_rect;
	BoundaryEdge m_edges[static_cast<int>(EdgeType::NUM_EDGES)];
	bool m_ReverseNormals;

	void SetupEdges();
};