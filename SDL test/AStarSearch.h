#pragma once
#include "TypeDefs.h"
#include "SparseGraph.h"
#include <unordered_map>
#include <memory>

using std::unordered_map;

class AStarSearch
{
public:
	AStarSearch() {}
	~AStarSearch() {}
	void search(const SparseGraph& graph, std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal, unordered_map<std::shared_ptr<GraphNode>, std::shared_ptr<GraphNode>>& came_from, unordered_map<std::shared_ptr<GraphNode>, double>& cost_so_far);
};

