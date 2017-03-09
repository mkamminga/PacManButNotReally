#pragma once
#include "BaseObject.h"
#include "BaseState.h"

class GamePlayObject :
	public BaseObject, public std::enable_shared_from_this<GamePlayObject>
{
	
protected:
	std::shared_ptr<GraphNode> currentNode = nullptr;
	std::unique_ptr<BaseState> currentState = nullptr;

	int health = 100;
	int alertness = 50;
	int attack = 40;

public:
	GamePlayObject(int x, int y) : BaseObject(x, y) {}
	virtual void setNode(std::shared_ptr<GraphNode> node);
	std::shared_ptr<GraphNode> getNode();
	virtual void update(double deltaTime) = 0;
	void setState(std::unique_ptr<BaseState> state);
	void setHealth(int health);
	int getHealth();
	void setAlertness(int alertness);
	int getAlertness();
	void setAttack(int attack);
	int getAttack();
	void useItems();
	~GamePlayObject() {}
};