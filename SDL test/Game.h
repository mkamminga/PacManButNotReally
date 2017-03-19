#pragma once
#include "SparseGraph.h"
#include "GhostManager.h"
#include "PacManObject.h"

class Game
{
private:
	std::shared_ptr<SparseGraph> graph;
	std::vector<std::shared_ptr<BaseVisitiable>> objects;
	std::vector<std::shared_ptr<GamePlayObject>> updateableGamePlayObjects;
	std::shared_ptr<GhostManager> ghostManager;
	std::shared_ptr<PacManObject> pacman;

public:
	Game() 
	{
		graph				= std::make_shared<SparseGraph>();
		ghostManager		= std::make_shared<GhostManager>();
	}
	void start();
	std::shared_ptr<SparseGraph> getGraph();
	bool shouldStartNewGeneration();
	void startNewGeneration();
	std::vector<std::shared_ptr<BaseVisitiable>>& gameObjects();
	std::vector<std::shared_ptr<GamePlayObject>>& gamePlayObjects();
};