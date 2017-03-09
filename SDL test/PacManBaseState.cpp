#include "PacManBaseState.h"
#include "GraphNode.h"
#include "PillItem.h"
#include "Random.h"
#include "GamePlayObject.h"

void PacManBaseState::update(double deltaTime)
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

	auto moveBy = (int)(ceil(50 * deltaTime));

	if (object->getX() != nextTarget->getX())
	{
		auto currentX = object->getX();
		auto targetX = nextTarget->getX();
		auto x = (targetX < currentX ? ((currentX - moveBy) < targetX ? targetX : currentX - moveBy) : ((currentX + moveBy) > targetX ? targetX : currentX + moveBy));
		object->setX(x);
	}
	if (object->getY() != nextTarget->getY())
	{
		auto currentY = object->getY();
		auto targetY = nextTarget->getY();
		auto y = (targetY < currentY ? ((currentY - moveBy) < targetY ? targetY : currentY - moveBy) : ((currentY + moveBy) > targetY ? targetY : currentY + moveBy));
		object->setY(y);
	}
}

void PacManBaseState::check()
{
	//nothing to check, will not change state
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
