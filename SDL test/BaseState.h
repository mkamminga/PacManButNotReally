#pragma once
#include <memory>
#include "BaseStateVisitable.h"
class GraphNode;

class GamePlayObject;

class BaseState: public BaseStateVisitiable {
protected:
	std::shared_ptr<GamePlayObject> object;
	std::shared_ptr<GraphNode> nextTarget = nullptr;
public:
	BaseState(std::shared_ptr<GamePlayObject> object) : object(object){}
	virtual void update(double deltaTime) = 0;
	virtual void check() = 0;
	virtual void accept(BaseVisitor* bv, BaseObject* bo) = 0;
	std::shared_ptr<GraphNode> getNextTarget();
	std::shared_ptr<GamePlayObject> getObject();
	virtual void updateAvgCatchTime() = 0;
protected:
	int moveBy(int from, int to, int by);
	void moveTo(std::shared_ptr<GamePlayObject> objectToUpdate, std::shared_ptr<GraphNode> target, int by);
	void moveTo(std::shared_ptr<GamePlayObject> objectToUpdate, std::shared_ptr<GamePlayObject> objectToMoveTo, int by);
};
