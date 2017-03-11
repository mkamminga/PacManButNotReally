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
	std::shared_ptr<Route> nextRoute = nullptr;
	std::shared_ptr<GraphNode> getNextNode()
	{
		auto currentRoute = nextRoute;

		if (currentRoute)
		{
			nextRoute = currentRoute->nextRoute;
			return currentRoute->node;
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
public:
	void addNode(std::shared_ptr<GraphNode>);
	const vector<std::shared_ptr<GraphNode>>& getNodes() const;
	void shortestPathTo(ShortestRoute& lastShortestRoute, std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal);
	std::shared_ptr<Route> search(std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal);
	const double calcDistance(const std::shared_ptr<GraphNode>, const std::shared_ptr<GraphNode>) const;
};




