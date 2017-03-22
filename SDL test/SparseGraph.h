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

	void resetRoute()
	{
		currentRoute = nullptr;
	}

	std::shared_ptr<GraphNode> getNextNode()
	{
		if (currentRoute)
		{
			auto node = currentRoute->node;
			currentRoute = currentRoute->nextRoute;
			return node;
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
	std::vector<std::shared_ptr<GraphNode>> nodes;
	std::vector<std::shared_ptr<Item>> items;
	std::map< std::pair< std::shared_ptr<GraphNode>, std::shared_ptr<GraphNode> >, std::shared_ptr<Route>> cachedRoutes;
	int cachedRouteLimit = 2000;
	int cachedRouteIndex = 0;
	int distanceMulitplier = 1;
public:
	void addNode(std::shared_ptr<GraphNode>);
	const vector<std::shared_ptr<GraphNode>>& getNodes() const;
	void addItem(std::shared_ptr<Item>);
	const vector<std::shared_ptr<Item>>& getItems() const;
	void shortestPathTo(ShortestRoute& lastShortestRoute, std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal);
	std::shared_ptr<Route> search(std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal);
	const double calcDistance(const std::shared_ptr<GraphNode>, const std::shared_ptr<GraphNode>) const;
	void setDistanceMulitplier(int distanceMulitplier);
	int getDistanceMulitplier();
};