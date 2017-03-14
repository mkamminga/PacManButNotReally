#include "GraphNode.h"
#include "SparseGraph.h"
#include <algorithm>

void GraphNode::addEdges(std::shared_ptr<GraphNode> to, double cost)
{
	auto position = std::find_if(edges.begin(), edges.end(), [to](const std::shared_ptr<GraphEdge> edge) {
		return to == edge->getTo();
	});

	if (position == edges.end())
	{
		edges.push_back(std::make_shared<GraphEdge>(this->shared_from_this(), to, cost));

		to->addEdges(this->shared_from_this(), cost);
	}

}

void GraphNode::addObject(std::shared_ptr<GamePlayObject> object)
{
	baseObjects.push_back(object);
	object->setNode(this->shared_from_this());
	object->setX(x);
	object->setY(y);
}

void GraphNode::removeObject(std::shared_ptr<GamePlayObject> toMatch)
{
	for (auto it = baseObjects.begin(); it != baseObjects.end(); it++)
	{
		auto object = it.operator*();
		if (object == toMatch) {
			baseObjects.erase(it);
			break;
		}
	}
}

void GraphNode::addItem(std::shared_ptr<Item> item)
{
	items.push_back(item);
	item->setNode(shared_from_this());
	item->setX(x);
	item->setY(y);
}

void GraphNode::removeItem(std::shared_ptr<Item> item)
{
	for (auto it = items.begin(); it != items.end(); it++)
	{
		auto object = it.operator*();
		if (object == item) {
			items.erase(it);
			item->setNode(nullptr);
			break;
		}
	}
}

const vector<std::shared_ptr<GraphEdge>>& GraphNode::getEdges() const
{
	return edges;
}

const vector<std::shared_ptr<GamePlayObject>>& GraphNode::getObjects() const
{
	return baseObjects;
}

const vector<std::shared_ptr<Item>>& GraphNode::getItems() const
{
	return items;
}

const std::shared_ptr<SparseGraph> GraphNode::getGraph() const
{
	return graph;
}

void GraphNode::accept(BaseVisitor * baseVisitor)
{
	baseVisitor->visit(this);
}
