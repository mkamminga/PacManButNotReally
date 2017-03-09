#pragma once
#include "BaseState.h"
#include "SparseGraph.h"

class CowChasing :
	public BaseState
{
private:
	ShortestRoute shortestRoute;
public:
	CowChasing(std::shared_ptr<GamePlayObject> object) : BaseState(object) {}
	virtual void update();
	virtual void check();
};

