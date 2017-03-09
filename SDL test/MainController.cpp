#include "MainController.h"
#include <thread>         // std::thread
#include <chrono>

void MainController::start()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		if (SDL_CreateWindowAndRenderer(1200, 600, 0, &window, &renderer) == 0) {

			mainView.setRenderer(renderer);
			std::thread UIUpdateFrame{ &MainController::play, this };
			feel();
			UIUpdateFrame.detach(); // do not wait for sleep, exit on stop
		}
	}

	shutdown();
}

void MainController::play()
{
	game.start();

	while (!done) {
		update();
		draw();
		std::this_thread::sleep_for(std::chrono::seconds(1));
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

void MainController::update()
{
	auto graph = game.getGraph();
	auto nodes = graph->getNodes();
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
