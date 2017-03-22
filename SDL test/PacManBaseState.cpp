#include "PacManBaseState.h"
#include "GraphNode.h"
#include "PillItem.h"
#include "Random.h"
#include "GamePlayObject.h"
#include "SparseGraph.h"
#include <iostream>

void PacManBaseState::update(double deltaTime)
{
	auto by = (int)(ceil(object->getSpeed() * object->getNode()->getGraph()->getDistanceMulitplier() * (object->getHealth() * 0.01) * deltaTime));

	while (by > 0)
	{
		if (!nextTarget || object->getNode() == nextTarget)
		{
			nextTarget = nullptr;
			calcNextTaget();
		}
	
		moveTo(object, nextTarget, by); // by is updated to the remaining sum
	}
}

void PacManBaseState::check()
{
	//nothing to check, will not change state, not ever
}

void PacManBaseState::calcNextTaget()
{
	auto node = object->getNode();
	auto edges = node->getEdges();
	auto size = (int)(edges.size() - 1);
	uniform_int_distribution<int> dist{ 0,  size };

	std::shared_ptr<GraphNode> newNode = nullptr;
	if (size > 0)
	{
		while (!newNode || (newNode == lastVisited[0] || newNode == lastVisited[1]))
		{
			int index = dist(dre);

			newNode = edges.at(index)->getTo();
		}

		lastVisited[1] = lastVisited[0];
		lastVisited[0] = node;
	}
	else
	{
		newNode = edges.at(0)->getTo();
	}

	nextTarget = newNode;
}
