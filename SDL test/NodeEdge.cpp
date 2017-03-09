#include "NodeEdge.h"
#include "GraphNode.h"

const std::shared_ptr<GraphNode> GraphEdge::getFrom() const
{
	return from;
}

const std::shared_ptr<GraphNode> GraphEdge::getTo() const
{
	return to;
}

const double GraphEdge::getCost() const
{
	return m_dCost;
}
