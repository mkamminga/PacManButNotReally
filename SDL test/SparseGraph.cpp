#include "SparseGraph.h"
#include <queue>
#include "Item.h"

void SparseGraph::addNode(std::shared_ptr<GraphNode> node) {
	nodes.push_back(node);
}

const vector<std::shared_ptr<GraphNode>>& SparseGraph::getNodes() const {
	return nodes;
}

void SparseGraph::addItem(std::shared_ptr<Item> item)
{
	items.push_back(item);
}

const vector<std::shared_ptr<Item>>& SparseGraph::getItems() const
{
	return items;
}

void SparseGraph::shortestPathTo(ShortestRoute& lastShortestRoute, std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal)
{
	if (!lastShortestRoute.initialized || lastShortestRoute.start != start || lastShortestRoute.goal != goal)
	{
		//reset
		lastShortestRoute.start = start;
		lastShortestRoute.goal = goal;

		lastShortestRoute.resetRoute();
		
		if (cachedRoutes.find(make_pair(start, goal)) == cachedRoutes.end())
		{
			if (cachedRoutes.size() >= cachedRouteLimit)
			{
				cachedRoutes.erase(cachedRoutes.begin()); // remove oldest cached route
			}
			//(re)calculate
			lastShortestRoute.currentRoute = search(start, goal);

			cachedRoutes[make_pair(start, goal)] = lastShortestRoute.currentRoute;
		}
		else
		{
			lastShortestRoute.currentRoute = cachedRoutes[make_pair(start, goal)];
		}

		if (!lastShortestRoute.initialized)
		{
			lastShortestRoute.initialized = true;
		}
	}
}

const double SparseGraph::calcDistance(const std::shared_ptr<GraphNode> from, const std::shared_ptr<GraphNode> to) const
{
	return abs(from->getY() - to->getY()) + abs(from->getX() - to->getX());
}

void SparseGraph::setDistanceMulitplier(int distanceMulitplier)
{
	this->distanceMulitplier = distanceMulitplier;
}

int SparseGraph::getDistanceMulitplier()
{
	return distanceMulitplier;
}

std::shared_ptr<Route> SparseGraph::search(std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal)
{
	std::unordered_map<std::shared_ptr<GraphNode>, std::shared_ptr<GraphNode>> came_from; 
	std::unordered_map<std::shared_ptr<GraphNode>, double> cost_so_far;

	auto cmp = [](const std::pair<double, std::shared_ptr<GraphNode>>& left, const std::pair<double, std::shared_ptr<GraphNode>>& right) { 
		return left.first > right.first; 
	};

	std::priority_queue<std::pair<double, std::shared_ptr<GraphNode>>, std::vector<std::pair<double, std::shared_ptr<GraphNode>>>, decltype(cmp)> frontier(cmp);
	frontier.push(std::make_pair(0, start));
	
	bool found = false;
	while (!frontier.empty()) {
		std::pair<double, std::shared_ptr<GraphNode>> pair = frontier.top();
		frontier.pop();

		const std::shared_ptr<GraphNode> current = pair.second;

		if (current == goal) {
			found = true;
			break;
		}

		for (auto next : current->getEdges()) {
			double new_cost = cost_so_far[current] + next->getCost();

			double oldCosts = 0;
			if (cost_so_far.find(next->getTo()) != cost_so_far.end()) // any parent linked to this node?
			{
				oldCosts = cost_so_far[next->getTo()];
			}

			if (!cost_so_far.count(next->getTo()) || new_cost < oldCosts) {
				
				cost_so_far[next->getTo()] = new_cost;
				new_cost = new_cost + calcDistance(current, next->getTo());
				frontier.push(std::make_pair(new_cost, next->getTo())); // push priority as real costs + heuristic costs
				came_from[next->getTo()] = current;
			}
		}
	}

	if (found)
	{
		std::shared_ptr<GraphNode> currentNode = came_from[goal];
		auto path = std::make_shared<Route>();
		path->node = goal;
		if (goal != start)
		{
			while (currentNode != start)
			{
				//route.push_back(currentNode);
				auto newPath = std::make_shared<Route>();
				newPath->nextRoute = path;
				newPath->node = currentNode;

				path = newPath;

				currentNode = came_from[currentNode];
			}
		}

		return path;
	}

	return nullptr;
}