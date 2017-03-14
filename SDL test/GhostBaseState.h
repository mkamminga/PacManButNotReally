#pragma once
#include "BaseState.h"

class GhostManager;

class GhostBaseState :
	public BaseState
{
protected:
	std::shared_ptr<GhostManager> ghostManager;
public:
	GhostBaseState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager) : ghostManager(ghostManager), BaseState(object) {}
	std::shared_ptr<GhostManager> getGhostManager();
};

