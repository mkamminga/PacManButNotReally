#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Dimensions.h"

class Button
{
private:
	SDL_Rect position;
	SDL_Renderer* renderer;
	SDL_Texture * texture;
	Dimension dimensions;
public:
	Button()
	{
		position.h = 50;
		position.w = 50;
	}

	void setRender(SDL_Renderer* renderer);
	void setPosition(int x, int y);
	void draw();
	bool hasBeenClicked(int x, int y);
};

