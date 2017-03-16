#include "GhostChasingState.h"
#include "GhostFlockingState.h"
#include "GhostManager.h"

void GhostChasingState::update(double deltaTime)
{
	auto currentNode = object->getNode(); 
	auto targetNode = object->getTarget()->getNode();
	auto by = (int)(ceil(object->getSpeed() * deltaTime));

	if (currentNode == targetNode) // on the same node as our target, pacman
	{
		auto pacman = object->getTarget();
		moveTo(object, pacman, by);

		if (object->getX() == pacman->getX() && object->getY() == pacman->getY())
		{
			object->setX(1100 - (object->getX() / 10));
			object->setY(object->getY() -(object->getY() / 10));
			//update pacman speed
			//pacman->setSpeed(pacman->getSpeed());
			object->setState(std::make_shared<GhostFlockingState>(object, ghostManager)); // change to chasing
			object->getFirstState()->updateAvgCatchTime();
			object->getState()->updateAvgCatchTime();
		}
		else
		{
			nextNode = object->getTarget()->getState()->getNextTarget();
		}
	}
	else
	{
		if (nextNode->getX() == object->getX() && nextNode->getY() == object->getY())
		{
			if (nextNode != object->getNode())
			{
				nextNode->addObject(object);
			}
			auto nextTarget = lastRoute.getNextNode();
			if (nextTarget) {
				nextNode = nextTarget;
			}
		}

		
		moveTo(object, nextNode, by);
	}
}

void GhostChasingState::check()
{
	auto currentNode = object->getNode();
	auto currentTargetNode = object->getTarget()->getNode();

	if (!lastRoute.initialized || (targetNode != currentTargetNode && nextNode && currentNode == nextNode))
	{
		currentNode->getGraph()->shortestPathTo(lastRoute, currentNode, object->getTarget()->getState()->getNextTarget());
		if (lastTarget != lastRoute.currentRoute->node)
		{
			nextNode = currentNode;
			lastTarget = nullptr;
		}
		else
		{
			nextNode = lastRoute.getNextNode();
		}

		targetNode = currentTargetNode;
	}
}

void GhostChasingState::updateAvgCatchTime()
{
	ghostManager->updateAvgCatchTime(this);
}

void GhostChasingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}
