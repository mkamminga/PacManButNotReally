#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <random>
#include <stdlib.h>
#include "MainVisitor.h"
#include "Game.h"

using namespace std;

class MainController
{
private:
	MainVisitor mainView;
	Game game;
	random_device dev;
	bool done = false;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int feel();
	void update(double deltaTime);
	void draw();
	void shutdown();
public:
	void start();
	void play();
	~MainController();
};

