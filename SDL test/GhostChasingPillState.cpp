#include "GhostChasingPillState.h"
#include "GhostChasingState.h"
#include "GhostWanderingState.h"

void GhostChasingPillState::update(double deltaTime)
{
	if (!target)
	{
		check();
	}
	if (!nextNode)
	{
		return;
	}

	try {
		if (nextNode->getX() == object->getX() && nextNode->getY() == object->getY())
		{
			if (nextNode != object->getNode())
			{
				nextNode->addObject(object);
				auto nextTarget = lastRoute.getNextNode();

				if (!nextTarget)
				{
					auto a = "";

					return;
				}
				else
				{
					nextNode = nextTarget;
				}
			}
		}

		auto by = (int)(ceil(object->getSpeed() * deltaTime));
		moveTo(object, nextNode, by);
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
				graph->shortestPathTo(lastRoute, currentNode, targetNode);

				target = targetNode;
				nextNode = lastRoute.getNextNode();
			}
			else
			{
				auto a = "";
			}
		}
	}
	if (currentNode == target)
	{
		object->setState(std::make_shared<GhostWanderingState>(object, ghostManager, object->getWanderingTime())); // change to chasing
	}
}

void GhostChasingPillState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}
