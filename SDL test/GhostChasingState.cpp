#include "GhostChasingState.h"

void GhostChasingState::update(double deltaTime)
{
	/*if (!lastRoute.initialized)
	{
		check();
	}

	try {

		auto currentNode = object->getNode();

		if (currentNode == lastRoute.goal)
		{
			return;
		}

		if (nextTarget != nextRoute->node && nextTarget != currentNode)
		{
			nextTarget = currentNode;
		}


		if (nextTarget->getX() == object->getX() && nextTarget->getY() == object->getY())
		{
			if (nextTarget != object->getNode())
			{
				nextTarget->addObject(object);
				if (lastRoute.nextRoute->nextRoute)
				{
					nextRoute = nextRoute->nextRoute;
				}
			}

			nextTarget = nextRoute->node;
		}

		auto by = (int)(ceil(object->getSpeed() * deltaTime));

		moveTo(object, nextTarget, by);
	}
	catch (std::exception& e)
	{
		auto a = e.what();
	}
	catch (...)
	{
		auto a = "";
	}*/
}

void GhostChasingState::check()
{
	/*auto currentNode = object->getNode();
	auto targetNode = object->getTarget()->getNode();
	if (currentNode != targetNode)
	{
		currentNode->getGraph()->shortestPathTo(lastRoute, currentNode, targetNode);
		nextRoute = lastRoute.nextRoute;

		if (!nextTarget)
		{
			nextTarget = nextRoute->node;
		}
	}*/
}

void GhostChasingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}
