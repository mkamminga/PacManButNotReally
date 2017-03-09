#include "CowChasing.h"
#include <random>
#include "Random.h"
#include "CowWandering.h"

void CowChasing::update()
{
	auto target = object->getTarget();
	if (target)
	{
		auto currentCowNode = object->getNode();
		auto graph = currentCowNode->getGraph();
		auto nodes = graph->getNodes();

		uniform_int_distribution<int> dist{ 0,  (int)(nodes.size() - 1) };
		if (target->getNode() != shortestRoute.goal) // update goal, hare has moved since last update
		{
			shortestRoute = graph->shortestPathTo(object->getNode(), target->getNode());
		}

		auto nextNode = shortestRoute.getNextNode();
		if (nextNode)
		{
			nextNode->addObject(object);
		}
	}
	
}

void CowChasing::check()
{
	auto target = object->getTarget();
	if (target)
	{
		auto currentCowNode = object->getNode();
		auto graph = currentCowNode->getGraph();
		auto nodes = graph->getNodes();

		uniform_int_distribution<int> dist{ 0,  (int)(nodes.size() - 1) };

		if (currentCowNode == target->getNode()) // if hare and cow are on the same node, move the hare to a randowm node
		{
			object->setAlertness(0);
			auto nextHareNode = currentCowNode;

			while (nextHareNode == currentCowNode) // chose a random new node
			{
				int nextHareNodeIndex = dist(dre);
				nextHareNode = nodes.at(nextHareNodeIndex);
			}
			nextHareNode->addObject(target);
			
			object->setState(move(std::make_unique<CowWandering>(object)));
			
		}
	}
}
