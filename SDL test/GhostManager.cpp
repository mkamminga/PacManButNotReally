#include "GhostManager.h"
#include "Random.h"
#include "GhostWanderingState.h"
#include "GhostChasingPillState.h"
#include "GhostChasingState.h"
#include <iostream>

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
		for (int i = 0; i < 25; i++)
		{
			auto ghost = std::make_shared<GhostObject>(target, 65, speedMultiplierDist(dre), wanderingTimeDist(dre));
			ghost->setState(std::make_shared<GhostWanderingState>(ghost, shared_from_this()));
			node->addObject(ghost);
			ghosts.push_back(ghost);
		}
	}
}

std::shared_ptr<GhostBaseState> GhostManager::getNextRandomState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GraphNode> target)
{
	uniform_int_distribution<int> dist{ 0,  totalNumberOfChanceDist };
	int num = dist(dre);
	int chancesFromRange = 0;
	int chancesTillRange = 0;

	for (auto item : chances)
	{
		chancesTillRange += item.second;

		if (num >= chancesFromRange && num <= chancesTillRange)
		{
			std::shared_ptr<GhostBaseState> state = nullptr;
			std::string key = item.first;
			if (key == "wandering")
			{
				state = std::make_shared<GhostWanderingState>(object, shared_from_this());
			}
			else if (key == "finding_pill")
			{
				state = std::make_shared<GhostChasingPillState>(object, shared_from_this(), target);
			}
			else if (key == "chasing_pacman")
			{
				state = std::make_shared<GhostChasingState>(object, shared_from_this(), target);
			}

			if (firstStates.find(object) == firstStates.end())
			{
				firstStates[object] = key;
			}

			return state;
		}

		chancesFromRange += item.second;
	}

	return nullptr;
}

std::vector<std::shared_ptr<GhostObject>> GhostManager::getSpawnedGhosts()
{
	return ghosts;
}

void GhostManager::tick()
{
	time++;

	if (time == 1 || time % 5 == 0)
	{
		double percentages = 0;

		auto currentChances = chances;

		std::cout	<< "\n" 
					<< "Current chances:" 
					<< "\n" 
					<< "===============" 
					<< "\n";
		for (auto item : currentChances)
		{
			double percentage = 1.00 / (totalNumberOfChanceDist * 1.00 / item.second) * 100;
			std::cout	<< "Percentage for " 
						<< (item.first) 
						<< ": " 
						<< percentage
						<< "\n";

		}

		std::cout << "AVG time: " << avgTime << "\n\n";
	}
}

void GhostManager::updateAvgCatchTime(std::shared_ptr<GamePlayObject> object)
{
	if (firstStates.find(object) != firstStates.end())
	{
		auto state = firstStates[object];

		if (numOfGhosts > 0)
		{
			if (time < avgTime)
			{
				chances[state]+= 5;
				totalNumberOfChanceDist+= 5;
			}
			else if (time > avgTime && chances[state] > 5) // limit of one, there should always be some chance
			{
				chances[state]-= 5;
				totalNumberOfChanceDist-= 5;
			}

			avgTime = (avgTime + time) * 1.00 / numOfGhosts;
		}
		else
		{
			avgTime = time;
			numOfGhosts++;
		}
		//TODO: update avg time 
	}
}
