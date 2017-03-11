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

void GamePlayObject::setState(std::unique_ptr<BaseState> state)
{
	currentState = move(state);
}

void GamePlayObject::setHealth(int health)
{
	this->health = health;
}

int GamePlayObject::getHealth()
{
	return health;
}

void GamePlayObject::setAlertness(int alertness)
{
	this->alertness = alertness;
}

int GamePlayObject::getAlertness()
{
	return alertness;
}

void GamePlayObject::setAttack(int attack)
{
	this->attack = attack;
}

int GamePlayObject::getAttack()
{
	return attack;
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

std::shared_ptr<GamePlayObject> GamePlayObject::getTarget()
{
	return target;
}
