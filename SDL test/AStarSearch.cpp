#include "AStarSearch.h"
#include <queue>
#include <functional>


using std::priority_queue;

void AStarSearch::search(const SparseGraph& graph, std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> goal, unordered_map<std::shared_ptr<GraphNode>, std::shared_ptr<GraphNode>>& came_from, unordered_map<std::shared_ptr<GraphNode>, double>& cost_so_far)
{
	priority_queue<std::pair<double, std::shared_ptr<GraphNode>>> frontier;
	frontier.push(std::make_pair(0, start));

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		std::pair<double, std::shared_ptr<GraphNode>> pair = frontier.top();
		frontier.pop();

		const std::shared_ptr<GraphNode> current = pair.second;

		if (current == goal) {
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
				double priority = new_cost + graph.calcDistance(current, next->getTo());
				frontier.push(std::make_pair(priority, next->getTo())); // push priority as real costs + heuristic costs
				came_from[next->getTo()] = current;
			}
		}
	}
}