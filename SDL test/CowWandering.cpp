#include "CowWandering.h"
#include "CowChasing.h"
#include "GraphNode.h"
#include "PillItem.h"
#include "Random.h"
#include "GamePlayObject.h"

void CowWandering::update()
{
	auto node	= object->getNode();
	auto edges	= node->getEdges();
	auto size	= (int)(edges.size() - 1);
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

	newNode->addObject(object);
	object->useItems();
}

void CowWandering::check()
{
	if (object->getAlertness() == 100)
	{
		object->setState(move(std::make_unique<CowChasing>(object)));
	}
}