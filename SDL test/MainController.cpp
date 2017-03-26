#include "MainController.h"
#include <thread>         // std::thread
#include <chrono>
#include <iostream>
#include "BasicTimer.h"

void MainController::start()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		if (SDL_CreateWindowAndRenderer(1200, 600, 0, &window, &renderer) == 0) {

			mainView.setRenderer(renderer);
			std::thread UIUpdateFrame{ &MainController::play, this }; // start the game loop
			feel(); // start feeling, proccess user input
			UIUpdateFrame.detach(); // do not wait for sleep, exit on stop
		}
	}

	shutdown();
}

void MainController::play()
{
	game.start();
	
	std::thread mainTimer([]() {
		mainTimer.setTimer(1000);
		mainTimer.start();
	});
	
	
	using clock = std::chrono::high_resolution_clock;
	auto lastTime = clock::now();
	auto currentTime = lastTime;
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	try {
		while (!done) {
			/*currentTime = clock::now();
			long diff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
			auto d = (double)(1 / 6000.0 * diff);*/

			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();

			deltaTime = (double)((NOW - LAST) * 1000 / SDL_GetPerformanceFrequency());

			update(1.00 / 600.00 * deltaTime);
			draw();
			lastTime = currentTime;
			//std::this_thread::sleep_for(std::chrono::milliseconds(25));
		}
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}

	mainTimer.join();
}

void MainController::draw()
{
	auto updateableObjects = game.gamePlayObjects();
	mainView.draw(game.gameObjects(), updateableObjects);
}

int MainController::feel()
{
	bool spedUp = false;
	while (!done) { // waiting for events to happen
		SDL_Event event;

		mainView.listenForEvents(event);

		if (event.type == SDL_QUIT) {
			done = true;
		}
		else if (event.type == SDL_MOUSEBUTTONUP && !spedUp)
		{
			game.speedUp();

			spedUp = true;
		}
	}

	return 0;
}

void MainController::update(double deltaTime)
{
	auto updateableObjects = game.gamePlayObjects();

	for (auto object : updateableObjects)
	{
		object->update(deltaTime);
	}

	if (game.shouldStartNewGeneration())
	{
		updateableObjects.clear();
		game.startNewGeneration();
	}
}

void MainController::shutdown()
{
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}

	if (window) {
		SDL_DestroyWindow(window);
	}
}

MainController::~MainController()
{
	shutdown();
}
