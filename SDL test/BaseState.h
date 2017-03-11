#pragma once
#include <memory>
#include "BaseStateVisitable.h"

class GamePlayObject;

class BaseState: public BaseStateVisitiable {
protected:
	std::shared_ptr<GamePlayObject> object;
public:
	BaseState(std::shared_ptr<GamePlayObject> object) : object(object){}
	virtual void update(double deltaTime) = 0;
	virtual void check() = 0;
	virtual void accept(BaseVisitor* bv, BaseObject* bo) = 0;
};
