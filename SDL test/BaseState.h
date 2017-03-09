#pragma once
#include <memory>

class GamePlayObject;

class BaseState {
protected:
	std::shared_ptr<GamePlayObject> object;
public:
	BaseState(std::shared_ptr<GamePlayObject> object) : object(object){}
	virtual void update(double deltaTime) = 0;
	virtual void check() = 0;
};
