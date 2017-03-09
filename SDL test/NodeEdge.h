#pragma once
#include <memory>
class GraphNode;

class GraphEdge
{
private:
	//the cost of traversing the edge
	double m_dCost;
	std::shared_ptr<GraphNode> from;
	std::shared_ptr<GraphNode> to;
public:
	//ctors
	GraphEdge(std::shared_ptr<GraphNode> from, std::shared_ptr<GraphNode> to, double cost) :m_dCost(cost),
		from(from),
		to(to)
	{}

	virtual ~GraphEdge() {}
	const std::shared_ptr<GraphNode> getFrom() const;
	const std::shared_ptr<GraphNode> getTo() const;
	const double getCost() const;
};