#include "GhostChasingState.h"

void GhostChasingState::update(double deltaTime)
{
	if (!lastRoute.initialized)
	{
		check();
	}

	auto currentNode = object->getNode();

	if (!nextTarget)
	{
		nextTarget = lastRoute.nextRoute->node;
	}
	else if (nextTarget && nextTarget != lastRoute.nextRoute->node)
	{
		nextTarget = object->getNode();
	}

	if (nextTarget->getX() == object->getX() && nextTarget->getY() == object->getY())
	{
		if (nextTarget != object->getNode()) 
		{
			nextTarget->addObject(object);
			if (lastRoute.nextRoute->nextRoute)
			{
				nextTarget = lastRoute.nextRoute->nextRoute->node;
			}
		}
		else
		{
			nextTarget = lastRoute.nextRoute->node;
		}
	}

	auto by = (int)(ceil(object->getSpeed() * deltaTime));

	moveTo(object, nextTarget, by);
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
