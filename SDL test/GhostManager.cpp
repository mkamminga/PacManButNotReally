#include "GhostManager.h"
#include "Random.h"
#include "GhostWanderingState.h"
#include "GhostChasingPillState.h"

GhostManager::GhostManager()
{
}

void GhostManager::addSpawningGround(std::shared_ptr<GraphNode> spawningGround)
{
	spawningGrounds.push_back(spawningGround);
}

void GhostManager::spawn(std::shared_ptr<GamePlayObject> target)
{
	uniform_int_distribution<int> speedMultiplierDist{ 1,  3 };
	uniform_int_distribution<int> wanderingTimeDist { 2,  8 };

	for (auto node : spawningGrounds)
	{
		for (int i = 0; i < 4; i++)
		{
			auto ghost = std::make_shared<GhostObject>(target, 40, speedMultiplierDist(dre), wanderingTimeDist(dre));
			ghost->setState(std::make_shared<GhostWanderingState>(ghost, shared_from_this()));
			node->addObject(ghost);
			ghosts.push_back(ghost);
		}
	}
}

std::vector<std::shared_ptr<GhostObject>> GhostManager::getSpawnedGhosts()
{
	return ghosts;
}

void GhostManager::tick()
{
	//TODO: update timer
}


GhostManager::~GhostManager()
{
}
