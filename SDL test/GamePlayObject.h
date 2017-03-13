#pragma once
#include "BaseObject.h"
#include "BaseState.h"

class GamePlayObject :
	public BaseObject, public std::enable_shared_from_this<GamePlayObject>
{
	
protected:
	std::shared_ptr<GraphNode> currentNode = nullptr;
	std::shared_ptr<BaseState> currentState = nullptr;
	std::shared_ptr<GamePlayObject> target;
	int health = 100;
	int alertness = 50;
	int attack = 40;
	int speed;
	int speedmultiplier;
	int wanderingTime;

public:
	GamePlayObject(int x, int y, std::shared_ptr<GamePlayObject> target, int speed, int speedmultiplier, int wanderingTime) : 
		target(target),
		speed(speed),
		speedmultiplier(speedmultiplier),
		wanderingTime(wanderingTime),
		BaseObject(x, y) {}
	virtual void setNode(std::shared_ptr<GraphNode> node);
	std::shared_ptr<GraphNode> getNode();
	virtual void update(double deltaTime) = 0;
	void setState(std::shared_ptr<BaseState> state);
	void setHealth(int health);
	int getHealth();
	void setAlertness(int alertness);
	int getAlertness();
	void setAttack(int attack);
	int getAttack();
	void useItems();
	int getWanderingTime();
	int getSpeed();
	void setSpeed(int speed);
	int getSpeedMultiplier();
	std::shared_ptr<GamePlayObject> getTarget();
	~GamePlayObject() {}
};