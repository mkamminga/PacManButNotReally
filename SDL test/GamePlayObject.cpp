#include "BaseState.h"
#include "GamePlayObject.h"
#include "GraphNode.h" 


void GamePlayObject::setNode(std::shared_ptr<GraphNode> node)
{
	if (currentNode)
	{
		currentNode->removeObject(shared_from_this());
	}

	currentNode = node;
}

std::shared_ptr<GraphNode> GamePlayObject::getNode()
{
	return currentNode;
}

void GamePlayObject::setState(std::shared_ptr<BaseState> state)
{
	currentState = state;
}

std::shared_ptr<BaseState> GamePlayObject::getFirstState()
{
	return firstState;
}

std::shared_ptr<BaseState> GamePlayObject::getState()
{
	return currentState;
}

void GamePlayObject::setHealth(int health)
{
	this->health = health;
}

int GamePlayObject::getHealth()
{
	return health;
}

void GamePlayObject::useItems()
{
	auto items = currentNode->getItems();
	if (items.size() > 0)
	{
		for (auto item : items)
		{
			item->execute(shared_from_this());
			currentNode->removeItem(item);
		}
	}
}

int GamePlayObject::getWanderingTime()
{
	return wanderingTime;
}

int GamePlayObject::getSpeed()
{
	return speed;
}

void GamePlayObject::setSpeed(int speed)
{
	this->speed = speed;
}

int GamePlayObject::getSpeedMultiplier()
{
	return speedmultiplier;
}

std::shared_ptr<GamePlayObject> GamePlayObject::getTarget()
{
	return target;
}
