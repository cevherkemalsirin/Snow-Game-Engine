#include "Game/BreakOut/Excluder.h"
#include "Math/Utils.h"
#include <cmath>

void Excluder::Init(const Rectangle2D& rect, bool reverseNormals)
{
	m_rect = rect;
	m_ReverseNormals = reverseNormals;
	SetupEdges();
}

bool Excluder::HasCollided(const Rectangle2D & rect, BoundaryEdge & edge) const
{
	if (m_rect.Intersects(rect))
	{
		float yMin = m_rect.GetTopLeftPoint().GetY() >= rect.GetTopLeftPoint().GetY() ? m_rect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
		float yMax = m_rect.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? m_rect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

		float ySize = yMax - yMin;

		float xMin = m_rect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? m_rect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
		float xMax = m_rect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? m_rect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

		float xSize = xMax - xMin;

		if (xSize > ySize)
		{
			if (rect.GetCenter().GetY() > m_rect.GetCenter().GetY())
			{
				edge = m_edges[static_cast<int>(EdgeType::BOTTOM_EDGE)];
			}
			else
			{
				edge = m_edges[static_cast<int>(EdgeType::TOP_EDGE)];
			}
		}
		else
		{
			if (rect.GetCenter().GetX() < m_rect.GetCenter().GetX())
			{
				edge = m_edges[static_cast<int>(EdgeType::LEFT_EDGE)];
			}
			else
			{
				edge = m_edges[static_cast<int>(EdgeType::RIGHT_EDGE)];
			}
		
		}
		return true;
	}
	return false;
}

Vector2D Excluder::GetCollisionOffset(const Rectangle2D& rect) const
{
	BoundaryEdge edge;
	Vector2D offset = Vector2D::ZERO;
	if (HasCollided(rect,edge))
	{
		float yMin = m_rect.GetTopLeftPoint().GetY() >= rect.GetTopLeftPoint().GetY() ? m_rect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
		float yMax = m_rect.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? m_rect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

		float ySize = yMax - yMin;

		float xMin = m_rect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? m_rect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
		float xMax = m_rect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? m_rect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

		float xSize = xMax - xMin;

		if (!math::FEqual(edge.normal.GetY(), 0.f))
		{
			offset = (ySize + 1) * edge.normal;
		}
		else
		{
			offset = (xSize + 1) * edge.normal;
		}
	}
	return offset;
}

void Excluder::MoveBy(const Vector2D& delta)
{
	m_rect.MoveBy(delta);
	SetupEdges();
}

void Excluder::MoveToPoint(const Vector2D & point)
{
	m_rect.MoveTo(point);
	SetupEdges();
}

const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const
{
	if (edge != EdgeType::NUM_EDGES)
	{
		return m_edges[static_cast<int>(edge)];
	}
}

void Excluder::SetupEdges()
{
	m_edges[static_cast<int>(EdgeType::TOP_EDGE)].edge = Line2D(m_rect.GetTopLeftPoint().GetX(), m_rect.GetTopLeftPoint().GetY(),
		m_rect.GetBottomRightPoint().GetX(), m_rect.GetTopLeftPoint().GetY());

	m_edges[static_cast<int>(EdgeType::TOP_EDGE)].normal = UP_DIR;

	m_edges[static_cast<int>(EdgeType::LEFT_EDGE)].edge = Line2D(m_rect.GetTopLeftPoint().GetX(), m_rect.GetTopLeftPoint().GetY(),
		m_rect.GetTopLeftPoint().GetX(), m_rect.GetBottomRightPoint().GetY());
	m_edges[static_cast<int>(EdgeType::LEFT_EDGE)].normal = LEFT_DIR;

	m_edges[static_cast<int>(EdgeType::RIGHT_EDGE)].edge = Line2D(m_rect.GetBottomRightPoint().GetX(), m_rect.GetTopLeftPoint().GetY(),
		m_rect.GetBottomRightPoint().GetX(), m_rect.GetBottomRightPoint().GetY());
	m_edges[static_cast<int>(EdgeType::RIGHT_EDGE)].normal = RIGTH_DIR;

	m_edges[static_cast<int>(EdgeType::BOTTOM_EDGE)].edge = Line2D(m_rect.GetTopLeftPoint().GetX(), m_rect.GetBottomRightPoint().GetY(),
		m_rect.GetBottomRightPoint().GetX(), m_rect.GetBottomRightPoint().GetY());
	m_edges[static_cast<int>(EdgeType::BOTTOM_EDGE)].normal = DOWN_DIR;

	if (m_ReverseNormals)
	{
		for (auto& edge : m_edges)
		{
			edge.normal = -edge.normal;
		}
	}

}
