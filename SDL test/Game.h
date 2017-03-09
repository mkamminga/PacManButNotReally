#pragma once
#include "CowObject.h"
#include "HareObject.h"
#include "SparseGraph.h"

class Game
{
private:
	std::shared_ptr<CowObject> cow;
	std::shared_ptr<HareObject> hare;
	std::shared_ptr<SparseGraph> graph;
	std::vector<std::shared_ptr<BaseVisitiable>> objects;

public:
	Game() 
	{
		hare = std::make_shared<HareObject>(0, 0, nullptr);
		cow = std::make_shared<CowObject>(0, 0, hare);
		graph = std::make_shared<SparseGraph>();
	}
	void start();
	std::shared_ptr<CowObject> getCow();
	std::shared_ptr<HareObject> getHare();
	std::shared_ptr<SparseGraph> getGraph();
	std::vector<std::shared_ptr<BaseVisitiable>>& gameObjects();
};