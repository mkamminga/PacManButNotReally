#include "MainController.h"
#include <thread>         // std::thread
#include <chrono>
#include <iostream>

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

	using clock = std::chrono::high_resolution_clock;
	auto lastTime = clock::now();
	auto currentTime = lastTime;
	try {
		while (!done) {
			currentTime = clock::now();
			long diff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
			auto d = (double)(1 / 600.0 * diff);
			update(d);
			draw();
			lastTime = currentTime;
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}
}

void MainController::draw()
{
	mainView.draw(game.gameObjects());
}

int MainController::feel()
{
	while (!done) { // waiting for events to happen
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = true;
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				//return 2;
			}
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
