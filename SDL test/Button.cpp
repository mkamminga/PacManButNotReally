#include "Button.h"

void Button::setRender(SDL_Renderer * renderer)
{
	this->renderer = renderer;

	texture = IMG_LoadTexture(renderer, "images/cow-2.png");
}

void Button::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;

	dimensions.height = position.h;
	dimensions.width = position.w;
	dimensions.x0 = x;
	dimensions.x1 = x + dimensions.width;
	dimensions.y0 = y;
	dimensions.y1 = y + dimensions.height;
}

void Button::draw()
{
	SDL_RenderCopy(renderer, texture, NULL, &position);
}

bool Button::hasBeenClicked(int x, int y)
{
	return dimensions.withinBounds(x, y);
}
