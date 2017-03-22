#include "GhostChasingPillState.h"
#include "GhostChasingState.h"
#include "GhostWanderingState.h"
#include "GhostManager.h"

void GhostChasingPillState::update(double deltaTime)
{
	if (!target)
	{
		return;
	}

	try {
		auto by = (int)(ceil(object->getSpeed() * object->getNode()->getGraph()->getDistanceMulitplier() * deltaTime));

		while (by > 0)
		{
			auto currentNode = object->getNode();
			if (currentNode == target)
			{
				//multiply speed by the multiplier
				object->setSpeed(object->getSpeed() * object->getNode()->getGraph()->getDistanceMulitplier() * object->getSpeedMultiplier());
				object->setState(std::make_shared<GhostChasingState>(object, ghostManager, nullptr)); // change to chasing
				break;
			}
			else
			{
				if (currentNode == nextNode)
				{
					auto nextTarget = lastRoute.getNextNode();
					if (nextTarget) {
						nextNode = nextTarget;
					}
				}

				moveTo(object, nextNode, by);
			}
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
