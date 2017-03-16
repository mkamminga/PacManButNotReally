#pragma once
#include "GhostObject.h"
#include "BasicTimer.h"
#include "GraphNode.h"
#include <map>

class GhostBaseState;
class GhostWanderingState;
class GhostChasingState;
class GhostChasingPillState;

class GhostManager : public BasicTimerRegisterAble, public std::enable_shared_from_this<GhostManager>
{
private:
	std::vector<std::shared_ptr<GhostObject>> ghosts;
	std::vector<std::shared_ptr<GraphNode>> spawningGrounds;
	std::map<std::string, int> chances;
	int totalNumberOfChanceDist = 0;
	long time;
public:
	GhostManager() 
	{
		chances["wandering"]		= 33;
		chances["finding_pill"]		= 33;
		chances["chasing_pacman"]	= 33;

		totalNumberOfChanceDist		= chances.size() * 33;
	}
	void addSpawningGround(std::shared_ptr<GraphNode> spawningGround);
	void spawn(std::shared_ptr<GamePlayObject> target);
	std::shared_ptr<GhostBaseState> getNextRandomState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GraphNode> target);
	std::vector<std::shared_ptr<GhostObject>> getSpawnedGhosts();
	virtual void tick();

	void updateAvgCatchTime(GhostWanderingState*);
	void updateAvgCatchTime(GhostChasingState*);
	void updateAvgCatchTime(GhostChasingPillState*);
};