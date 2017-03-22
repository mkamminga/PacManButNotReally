#include "GhostChasingState.h"
#include "GhostFlockingState.h"
#include "GhostManager.h"

void GhostChasingState::update(double deltaTime)
{

	auto by = (int)(ceil(object->getSpeed() * object->getNode()->getGraph()->getDistanceMulitplier() * deltaTime));

	while (by > 0)
	{
		auto currentNode = object->getNode();
		auto targetNode = object->getTarget()->getNode();
		auto targetTravlingToNode = object->getTarget()->getState()->getNextTarget();
		if (currentNode == targetNode || currentNode == targetTravlingToNode) // on the same node as our target, pacman
		{
			auto pacman = object->getTarget();

			if (object->getX() == pacman->getX() && object->getY() == pacman->getY())
			{
				object->setX(1100 - (object->getX() / 10));
				object->setY(object->getY() - (object->getY() / 10));
				//remove from object
				currentNode->removeObject(object);
				object->setNode(nullptr);
				//TODO: update pacman speed
				pacman->setHealth(pacman->getHealth() - 1);
				ghostManager->updateAvgCatchTime(object);
				ghostManager->addToCrossoverList(object);

				object->setState(std::make_shared<GhostFlockingState>(object, ghostManager)); // change to chasing
				break;

			}
			else
			{
				moveTo(object, pacman, by);
				nextNode = targetTravlingToNode;
			}
		}
		else
		{
			if (currentNode == nextNode)
			{
				auto nextTarget = lastRoute.getNextNode();
				if (nextTarget) 
				{
					nextNode = nextTarget;
				}
				else
				{
					check();
				}
			}

			moveTo(object, nextNode, by);
		}
	}
}

void GhostChasingState::check()
{
	auto currentNode = object->getNode();
	auto currentTargetNode = object->getTarget()->getNode();

	if (!lastRoute.initialized || (targetNode != currentTargetNode && nextNode && currentNode == nextNode))
	{
		currentNode->getGraph()->shortestPathTo(lastRoute, currentNode, currentTargetNode);
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

void GhostChasingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}
