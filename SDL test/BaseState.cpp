#include "BaseState.h"
#include "GraphNode.h"

int BaseState::moveBy(int from, int to, int by)
{
	if (to  < from)
	{
		return ((from - by) < to) ? to : (from - by);
	}
	else
	{
		return ((from + by) > to) ? to : (from + by);
	}
}

void BaseState::moveTo(std::shared_ptr<GamePlayObject> objectToUpdate, std::shared_ptr<GraphNode> target, int by)
{

	if (objectToUpdate->getX() != target->getX())
	{
		auto currentX = object->getX();
		auto targetX = target->getX();
		auto x = moveBy(currentX, targetX, by);
		objectToUpdate->setX(x);
	}

	if (objectToUpdate->getY() != target->getY())
	{
		auto currentY = object->getY();
		auto targetY = target->getY();
		auto y = moveBy(currentY, targetY, by);
		objectToUpdate->setY(y);
	}
}
