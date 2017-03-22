#include "BaseState.h"
#include "GraphNode.h"
#include "GamePlayObject.h"
#include "SparseGraph.h"
#include <iostream>

std::shared_ptr<GraphNode> BaseState::getNextTarget()
{
	return nextTarget;
}

std::shared_ptr<GamePlayObject> BaseState::getObject()
{
	return object;
}

int BaseState::moveBy(int from, int to, int& by)
{
	int moveToBy = 0;

	if (to <= from)
	{

		if ((from - by) < to) 
		{
			moveToBy = to;

			by = (by - (from - to));
		}
		else
		{
			moveToBy = (from - by);
			by = 0;
		}
	}
	else
	{
		if ((from + by) >= to)
		{
			moveToBy = to;

			by = (by - (to - from));
		}
		else
		{
			moveToBy = (from + by);
			by = 0;
		}
	}

	return moveToBy;
}

void BaseState::moveTo(std::shared_ptr<GamePlayObject> objectToUpdate, std::shared_ptr<GraphNode> target, int& by)
{
	int moveByRemainingX	= by;
	int moveByRemainingY	= by;

	if (objectToUpdate->getX() != target->getX())
	{
		auto currentX = object->getX();
		auto targetX = target->getX();
		objectToUpdate->setX( moveBy(currentX, targetX, moveByRemainingX) );
	}

	if (objectToUpdate->getY() != target->getY())
	{
		auto currentY = object->getY();
		auto targetY = target->getY();
		objectToUpdate->setY(moveBy(currentY, targetY, moveByRemainingY));
	}


	auto distX = abs(objectToUpdate->getNode()->getX() - target->getX());
	auto distY = abs(objectToUpdate->getNode()->getY() - target->getY());

	if (distX > distY) // update by to the the largest remaining sum
	{
		by = moveByRemainingX; 
	}
	else
	{
		by = moveByRemainingY;
	}

	if (objectToUpdate->getX() == target->getX() && objectToUpdate->getY() == target->getY())
	{
		target->addObject(object);
	}
}

void BaseState::moveTo(std::shared_ptr<GamePlayObject> objectToUpdate, std::shared_ptr<GamePlayObject> objectToMoveTo, int& by)
{
	int moveByRemainingX	= by;
	int moveByRemainingY	= by;

	if (objectToUpdate->getX() != objectToMoveTo->getX())
	{
		auto currentX = object->getX();
		auto targetX = objectToMoveTo->getX();
		objectToUpdate->setX(moveBy(currentX, targetX, moveByRemainingX));
	}

	if (objectToUpdate->getY() != objectToMoveTo->getY())
	{
		auto currentY = object->getY();
		auto targetY = objectToMoveTo->getY();
		auto y = moveBy(currentY, targetY, moveByRemainingY);
		objectToUpdate->setY(y);
	}

	auto distX = abs(objectToUpdate->getX() - objectToMoveTo->getX());
	auto distY = abs(objectToUpdate->getY() - objectToMoveTo->getY());

	if (distX > distY) // update by to the the largest remaining sum
	{
		by = moveByRemainingX;
	}
	else
	{
		by = moveByRemainingY;
	}
}
