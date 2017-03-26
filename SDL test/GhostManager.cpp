#include "GhostManager.h"
#include "Random.h"
#include "GhostWanderingState.h"
#include "GhostChasingPillState.h"
#include "GhostChasingState.h"
#include <iostream>
#include <iterator>

void GhostManager::addSpawningGround(std::shared_ptr<GraphNode> spawningGround)
{
	spawningGrounds.push_back(spawningGround);
}

void GhostManager::spawn(std::shared_ptr<GamePlayObject> target)
{
	uniform_int_distribution<int> speedMultiplierDist{ 1,  3 };
	uniform_int_distribution<int> wanderingTimeDist { 2,  8 };
	uniform_int_distribution<int> speedDist{ 51,  70 };
	int overallSpeed = 0;
	int overallWanderingTime = 0;
	int overallSpeedmultiplier = 0;
	for (auto node : spawningGrounds)
	{
		for (int i = 0; i < 25; i++)
		{
			auto speedMulitplier			= speedMultiplierDist(dre);
			auto wanderingTime				= wanderingTimeDist(dre);
			auto speed						= speedDist(dre);

			auto ghost = std::make_shared<GhostObject>(target, speed, speedMulitplier, wanderingTime);
			ghost->setState(std::make_shared<GhostWanderingState>(ghost, shared_from_this()));
			node->addObject(ghost);
			ghosts.push_back(ghost);

			overallSpeed += speed;
			overallSpeedmultiplier += speedMulitplier;
			overallWanderingTime += wanderingTime;
		}
	}
	auto size = ghosts.size();

	std::cout << "\n"
		<< "Generation AVG:"
		<< "\n"
		<< "*===============*"
		<< "\n"
		<< "Speed: " << (overallSpeed * 1.00 / size) << endl
		<< "Speed mltp *: " << (overallSpeedmultiplier * 1.00 / size) << endl
		<< "Wandering time: " << (overallWanderingTime * 1.00 / size) << endl
		<< "*===============*"
		<< "\n";
}

void GhostManager::spawnByCrossover(std::shared_ptr<GamePlayObject> target)
{
	std::list<std::shared_ptr<GamePlayObject>> selectedCrossOverList;
	std::list<std::pair<std::shared_ptr<GamePlayObject>, std::shared_ptr<GamePlayObject>>> selectedMatchedCrossOverList;

	selectForNextGeneration(selectedCrossOverList);
	matchSelections(selectedCrossOverList, selectedMatchedCrossOverList);

	uniform_int_distribution<int> mutationDist		{ 300,  1000 };
	uniform_int_distribution<int> speedDividerDist	{ 2,  4 };
	uniform_int_distribution<int> wanderingTimeDist		{ 1, 2 };

	auto it							= selectedMatchedCrossOverList.begin();
	int size						= selectedMatchedCrossOverList.size();
	int overallSpeed				= 0;
	int overallWanderingTime		= 0;
	int overallSpeedmultiplier		= 0;

	for (auto node : spawningGrounds)
	{
		for (int i = 0; i < 25; i++)
		{
			auto objects = it.operator*();

			auto from = objects.first;
			auto with = objects.second;

			int speed				= 0;
			int speedMulitplier		= 0;
			int wanderingTime		= 0;

			speed			= crossOverValues(from->getSpeed(), with->getSpeed(), speedDividerDist(dre));
			wanderingTime	= crossOverValues(from->getWanderingTime(), with->getWanderingTime(), wanderingTimeDist(dre));
			speedMulitplier = crossOverValues(from->getSpeedMultiplier(), with->getSpeedMultiplier(), 1);

			auto mutaion = mutationDist(dre);

			if (mutaion >= 998) // apply mutations
			{
				applyMutation(wanderingTime, speed, speedMulitplier, mutaion);
			}

			if (speed > 2000) // safe guard maximum speed
			{
				speed = 2000;
			}

			//update avg
			overallSpeed += speed;
			overallSpeedmultiplier += speedMulitplier;
			overallWanderingTime += wanderingTime;

			auto ghost = std::make_shared<GhostObject>(target, speed, speedMulitplier, wanderingTime);
			ghost->setState(std::make_shared<GhostWanderingState>(ghost, shared_from_this()));
			node->addObject(ghost);
			ghosts.push_back(ghost);

			if (it != selectedMatchedCrossOverList.end())
			{
				it++;
			}
		}
	}

	crossoverList.clear();

	std::cout << "\n"
		<< "Generation AVG:"
		<< "\n"
		<< "*===============*"
		<< "\n"
		<< "Speed: " << (overallSpeed * 1.00 / size) << endl
		<< "Speed mltp *: " << (overallSpeedmultiplier * 1.00 / size) << endl
		<< "Wandering time: " << (overallWanderingTime * 1.00 / size) << endl
		<< "*===============*"
		<< "\n";
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
	int a = 5;

	if (time == 1 || time % informationTicks == 0)
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

		if (avgTime >= 0 && numOfGhosts > 0)
		{
			std::cout << "AVG time: " << (avgTime / numOfGhosts) << "\n\n";
		}
	}
}

void GhostManager::updateAvgCatchTime(std::shared_ptr<GamePlayObject> object)
{
	if (firstStates.find(object) != firstStates.end())
	{
		auto state = firstStates[object];
		numOfGhosts++;
		if (numOfGhosts > 1)
		{
			if (time < avgTime)
			{
				chances[state]+= 1;
				totalNumberOfChanceDist+= 1;
			}
			else if (time > avgTime && chances[state] > 0) // limit of one, there should always be some chance
			{
				chances[state]-= 1;
				totalNumberOfChanceDist-= 1;

				if (totalNumberOfChanceDist <= 0)
				{
					totalNumberOfChanceDist = 1;
				}
			}

			avgTime += time;
		}
		else
		{
			avgTime = time;
		}
	}
}

void GhostManager::addToCrossoverList(std::shared_ptr<GamePlayObject> object)
{
	int value	=	10000 - time; // subtract the time it took to catch pacman
	value		-= (object->getWanderingTime() * 1000);
	value		+=	ceil(object->getSpeed() * 20);
	value		+=	object->getSpeedMultiplier() * 100;

	crossoverList.push_back(make_pair(value, object));
}

void GhostManager::resetForNextGeneration()
{
	time = 0;
	firstStates.clear();
	for (auto ghost : ghosts)
	{
		ghost->setState(nullptr);
	}

	ghosts.clear();
	flockingWorld->clear();
}

void GhostManager::setDisplayInformationTicks(int ticks)
{
	informationTicks = ticks;
}

std::shared_ptr<FlockingWorld> GhostManager::getWorld()
{
	return flockingWorld;
}

void GhostManager::selectForNextGeneration(std::list<std::shared_ptr<GamePlayObject>>& selectedCrossOverList)
{
	/*
		CALC POTENTIAL Candidates
	*/
	int total = 0;
	double avg;

	for (auto item : crossoverList)
	{
		total += item.first; // calc total
	}

	avg = (total * 1.0) / crossoverList.size();

	std::list<std::pair<double, std::shared_ptr<GamePlayObject>>> sortedProjectedBreadingPotentialList; // define lists used for breeding, sorted by highest value and therefor breadign potential
	std::list<std::pair<double, std::shared_ptr<GamePlayObject>>> highValueBreadingPotentialList;
	//Calc potential in new population
	int avgMulitplier = ceil(avg);
	for (auto item : crossoverList)
	{
		double num = ((item.first * 1.00) / total) * avgMulitplier; // projected breading potentiel, higher is better
		sortedProjectedBreadingPotentialList.push_back(make_pair(num, item.second));
	}

	auto cmp = [](const std::pair<double, std::shared_ptr<GamePlayObject>>& left, const std::pair<double, std::shared_ptr<GamePlayObject>>& right) { return left.first > right.first; };
	sortedProjectedBreadingPotentialList.sort(cmp);

	highValueBreadingPotentialList = sortedProjectedBreadingPotentialList;
	//remove any factional values below 1 = < 0 
	highValueBreadingPotentialList.remove_if([](const std::pair<double, std::shared_ptr<GamePlayObject>>& item) {
		return ceil(item.first) < 1;
	});

	int numToCrossover = sortedProjectedBreadingPotentialList.size();
	/*
		SELECT POTENTIAL Candidates
	*/
	for (auto item : highValueBreadingPotentialList)
	{
		selectedCrossOverList.push_back(item.second);
		numToCrossover--;
	}

	if (numToCrossover > 0 )
	{
		//Sort by decimals
		/*auto cmp = [](const std::pair<double, std::shared_ptr<GamePlayObject>>& left, const std::pair<double, std::shared_ptr<GamePlayObject>>& right) { 
			double leftValue	= left.first - ((int)left.first);
			double rightValue	= right.first - ((int)right.first);
			
			return leftValue > rightValue;
		};
		//Add selected decimals until
		sortedProjectedBreadingPotentialList.sort(cmp);*/
		for (auto item : sortedProjectedBreadingPotentialList) // copy until requierd num of objects is reached
		{
			selectedCrossOverList.push_back(item.second);
			numToCrossover--;

			if (numToCrossover <= 0)
			{
				break;
			}
		}
	}
}

void GhostManager::matchSelections(std::list<std::shared_ptr<GamePlayObject>>& selectedCrossOverList, std::list<std::pair<std::shared_ptr<GamePlayObject>, std::shared_ptr<GamePlayObject>>>& selectedMatchedCrossOverList)
{
	uniform_int_distribution<int> indexToMatchDist{ 0,  99 };
	std::vector<std::shared_ptr<GamePlayObject>> toMatchFrom;
	std::copy(selectedCrossOverList.begin(), selectedCrossOverList.end(), std::back_inserter(toMatchFrom));

	auto size = selectedCrossOverList.size();
	int i = 0;
	for (auto object : selectedCrossOverList)
	{
		int num = indexToMatchDist(dre);
		
		if (num == i)
		{
			num = (i > 0 ? num - 1 : (size > 0 ? 1 : 0));
		}
		auto match = toMatchFrom.at(num);
		
		selectedMatchedCrossOverList.push_back(std::make_pair(object, match));
		i++;
	}
}

int GhostManager::crossOverValues(int base, int with, int separateOn)
{
	int bitLengh = floor(log2(base)) + 1;	// determine bit length
	int shiftBy = bitLengh - separateOn;	// determine shift position
	
	if (shiftBy < 0)
	{
		shiftBy = 0;
	}

	if (bitLengh > 1) {
		base = (base >> shiftBy) << shiftBy; // shift to left, and right leaving the needed bits
	}

	int numberOFBits = shiftBy * shiftBy;
	if (numberOFBits <= 1)
	{
		numberOFBits = 2;
	}

	with = (with & (numberOFBits - 1)); // trim of to use only the needed bits

	return base | with;
}

void GhostManager::applyMutation(int & wanderingTime, int & speed, int & speedMulitplier, int mutation)
{
	uniform_int_distribution<int> worseOffDist{ 1, 2 };
	auto worseOffChoice = worseOffDist(dre);
	// perform mutations
	if (mutation == 998) // wandering time
	{
		wanderingTime = (worseOffChoice == 2 ? wanderingTime >> 1 : wanderingTime << 1);
		wanderingTime = (wanderingTime > 8 ? 8 : (wanderingTime < 2) ? 2 : wanderingTime);
	}
	else if (mutation == 999) // speed mulitplier, add or subtract -/+ 1 if more than one and less than three
	{
		speedMulitplier = (worseOffChoice == 2 ? (speedMulitplier < 3 ? speedMulitplier + 1 : speedMulitplier) : speedMulitplier > 1 ? speedMulitplier - 1 : speedMulitplier);
	}
	else if (mutation == 1000) // speed
	{
		speed = worseOffChoice == 2 ? speed << 1 : speed >> 1;
		speed = speed < 30 ? 30 : speed;
	}
}
