#pragma once
#include "GhostObject.h"
#include "BasicTimer.h"
#include "GraphNode.h"
#include <map>
#include <string>
#include <list>

class GhostBaseState;
class GhostWanderingState;
class GhostChasingState;
class GhostChasingPillState;
class GhostBaseState;

class GhostManager : public BasicTimerRegisterAble, public std::enable_shared_from_this<GhostManager>
{
private:
	std::vector<std::shared_ptr<GhostObject>>			ghosts;
	std::vector<std::shared_ptr<GraphNode>>				spawningGrounds;
	std::map<std::string, int>							chances;

	std::map<std::shared_ptr<GamePlayObject>, std::string>			firstStates;
	std::vector<std::pair<int, std::shared_ptr<GamePlayObject>>>	crossoverList;

	int totalNumberOfChanceDist = 0;
	int numOfGhosts				= 0;
	double avgTime				= 0;
	int time					= 0;
	int informationTicks		= 5;

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
	void spawnByCrossover(std::shared_ptr<GamePlayObject> target);
	std::shared_ptr<GhostBaseState> getNextRandomState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GraphNode> target);
	std::vector<std::shared_ptr<GhostObject>> getSpawnedGhosts();
	virtual void tick();
	void updateAvgCatchTime(std::shared_ptr<GamePlayObject> object);
	void addToCrossoverList(std::shared_ptr<GamePlayObject> object);
	void resetForNextGeneration();
	void setDisplayInformationTicks(int ticks);
private:
	void selectForNextGeneration(std::list<std::shared_ptr<GamePlayObject>>& selectedCrossOverList);
	void matchSelections(std::list<std::shared_ptr<GamePlayObject>>& selectedCrossOverList, std::list<std::pair<std::shared_ptr<GamePlayObject>, std::shared_ptr<GamePlayObject>>> & selectedMatchedCrossOverList);
	int crossOverValues(int base, int with, int separateOn);
	void applyMutation(int& wanderingTime,int& speed, int& speedMulitplier, int mutation);
};