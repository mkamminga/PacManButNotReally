#include "GhostChasingPillState.h"
#include "GhostChasingState.h"
#include "GhostWanderingState.h"

void GhostChasingPillState::update(double deltaTime)
{
	if (!target)
	{
		return;
	}

	try {
		
		auto currentNode = object->getNode();
		if (currentNode == target)
		{
			//multiply speed by the multiplier
			object->setSpeed( object->getSpeed() * object->getSpeedMultiplier());
			object->setState(std::make_shared<GhostChasingState>(object, ghostManager, nullptr)); // change to chasing
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

			auto by = (int)(ceil(object->getSpeed() * deltaTime));
			moveTo(object, nextNode, by);
		}
	}
	catch (std::exception& e)
	{
		auto a = e.what();
	}
	catch (...)
	{
		auto a = "";
	}
}

void GhostChasingPillState::check()
{
	auto currentNode = object->getNode();
	if (!target) 
	{
		auto graph			= currentNode->getGraph();

		std::shared_ptr<GraphNode> targetNode = nullptr;

		auto items = graph->getItems();
		int shortestDistance = -1;

		if (items.size() > 0)
		{
			for (auto item : items)
			{
				auto itemNode = item->getNode();
				int distance = graph->calcDistance(currentNode, itemNode);
				if (shortestDistance < 0 || distance < shortestDistance)
				{
					targetNode = itemNode;
					shortestDistance = distance;
				}
			}

			if (targetNode)
			{
				target = targetNode;
				if (currentNode != targetNode)
				{
					graph->shortestPathTo(lastRoute, currentNode, targetNode);
					if (oldTarget != lastRoute.currentRoute->node)
					{
						nextNode = currentNode;
						oldTarget = nullptr;
					}
					else
					{
						nextNode = lastRoute.getNextNode();
					}
				}
				else
				{
					nextNode = nullptr;
				}
			}
		}
	}

}

void GhostChasingPillState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}
