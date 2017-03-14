#pragma once
#include "GhostObject.h"
#include "BasicTimer.h"
#include "GraphNode.h"

class GhostManager : public BasicTimerRegisterAble, public std::enable_shared_from_this<GhostManager>
{
private:
	std::vector<std::shared_ptr<GhostObject>> ghosts;
	std::vector<std::shared_ptr<GraphNode>> spawningGrounds;

public:
	GhostManager();
	void addSpawningGround(std::shared_ptr<GraphNode> spawningGround);
	void spawn(std::shared_ptr<GamePlayObject> target);
	std::vector<std::shared_ptr<GhostObject>> getSpawnedGhosts();
	virtual void tick();
	~GhostManager();
};

