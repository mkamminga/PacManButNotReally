#pragma once
#include "TypeDefs.h"
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include "GraphNode.h"

struct Route {
	std::shared_ptr<GraphNode> node = nullptr;
	std::shared_ptr<Route> nextRoute = nullptr;
};

struct ShortestRoute
{
	bool initialized = false;
	std::shared_ptr<GraphNode> start = nullptr;
	std::shared_ptr<GraphNode> goal = nullptr;
	int index = 0;
	std::shared_ptr<Route> currentRoute = nullptr;
	std::vector<std::shared_ptr<GraphNode>> route;

	void resetRoute()
	{
		route.clear();
		
		index = 0;
	}

	std::shared_ptr<GraphNode> getNextNode()
	{
		auto size =  route.size();
		if (index < size)
		{
			auto it = route.rbegin() + index;
			auto node = it.operator*();

			index++;

			return node;
		}
		else if (index == size)
		{
			return goal;
		}
		else
		{
			return nullptr;
		}
	}
};


class SparseGraph
{
private:
	vector<std::shared_ptr<GraphNode>> nodes;
	vector<std::shared_ptr<Item>> items;
public:
	void addNode(std::shared_ptr<GraphNode>);
	const vector<std::shared_ptr<GraphNode>>& getNodes() const;
	void addItem(std::shared_ptr<Item>);
	const vector<std::shared_ptr<Item>>& getItems() const;
	void shortestPathTo(ShortestRoute& lastShortestRoute, std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal);
	void search(std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal, std::vector<std::shared_ptr<GraphNode>>& route);
	const double calcDistance(const std::shared_ptr<GraphNode>, const std::shared_ptr<GraphNode>) const;
};




