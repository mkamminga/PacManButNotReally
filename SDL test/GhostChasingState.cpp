#include "GhostChasingState.h"

void GhostChasingState::update(double deltaTime)
{
	if (!lastRoute.initialized)
	{
		check();
	}

	auto currentNode = object->getNode();

	auto nextTarget = lastRoute.nextRoute->node;

	if (nextTarget->getX() == object->getX() && nextTarget->getY() == object->getY())
	{
		nextTarget->addObject(object);

		if (lastRoute.nextRoute->nextRoute)
		{
			auto nextTarget = lastRoute.nextRoute->nextRoute;
		}
	}

	if (currentNode == nextTarget)
	{
		return;
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

void GhostChasingState::check()
{
	auto currentNode = object->getNode();
	auto targetNode = object->getTarget()->getNode();
	if (currentNode != targetNode)
	{
		currentNode->getGraph()->shortestPathTo(lastRoute, currentNode, targetNode);
	}
	
}

void GhostChasingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}
