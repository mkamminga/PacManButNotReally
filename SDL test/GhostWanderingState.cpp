#include "GhostWanderingState.h"
#include "GhostChasingState.h"
#include "GhostChasingPillState.h"
#include <iostream>
#include "Random.h"

void GhostWanderingState::update(double deltaTime)
{
	if (!nextTarget)
	{
		calcNextTaget();
	}
	else if (nextTarget->getX() == object->getX() && nextTarget->getY() == object->getY())
	{
		nextTarget->addObject(object);
		nextTarget = nullptr;
		calcNextTaget();
	}

	auto by = (int)(ceil(object->getSpeed() * deltaTime));

	moveTo(object, nextTarget, by);
}

void GhostWanderingState::check()
{
	if (!registerd)
	{
		auto shared = shared_from_this();
		mainTimer.subscribe(shared);
		registerd = true;
	}

	auto currentItems = object->getNode()->getItems();

	try {
		if (wanderingTime == 0)
		{
			mainTimer.unsubscribe(shared_from_this());

			uniform_int_distribution<int> dist{ 1,  3 };
			int num = dist(dre);

			object->setState(std::make_shared<GhostChasingPillState>(object, ghostManager));
			/*
			if (num == 1)
			{
				object->setState(std::make_shared<GhostChasingState>(object, ghostManager));
			}
			else if (num == 2)
			{
				object->setState(std::make_shared<GhostChasingPillState>(object, ghostManager));
			}
			else
			{
				registerd = false;
				wanderingTime = object->getWanderingTime();
			}*/
		}
	}
	catch (std::exception& e)
	{
		auto a = e.what();
	}
}

void GhostWanderingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}

void GhostWanderingState::tick()
{
	if (wanderingTime > 0)
	{
		wanderingTime--;
	}
}

void GhostWanderingState::calcNextTaget()
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
