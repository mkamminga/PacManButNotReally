#pragma once
#include "BaseObject.h"
#include "BaseState.h"
#include "Vector2D.h"

class GamePlayObject :
	public BaseObject, public std::enable_shared_from_this<GamePlayObject>
{
	
protected:
	std::shared_ptr<GraphNode> currentNode = nullptr;
	std::shared_ptr<BaseState> currentState = nullptr;
	std::shared_ptr<BaseState> firstState = nullptr;
	std::shared_ptr<GamePlayObject> target;
	Vector2D heading;
	int health = 100;
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
	virtual void setState(std::shared_ptr<BaseState> state);
	std::shared_ptr<BaseState> getState();
	void setHealth(int health);
	int getHealth();
	void useItems();
	int getWanderingTime();
	int getSpeed();
	void setSpeed(int speed);
	int getSpeedMultiplier();
	Vector2D& getHeading();
	void setHeading(const Vector2D& heading);
	const Vector2D getPosition() const;
	std::shared_ptr<GamePlayObject> getTarget();
};