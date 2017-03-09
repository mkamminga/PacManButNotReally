#include "MainVisitor.h"
#include "BaseObject.h"
#include "CowObject.h"
#include "HareObject.h"
#include "GraphNode.h"
#include "NodeEdge.h"
#include "SparseGraph.h"
#include "PillItem.h"
#include "GunItem.h"

void drawcircle(SDL_Renderer* renderer, int x0, int y0, int radius)
{
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
		SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
		SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
		SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
		SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
		SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
		SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
		SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void MainVisitor::setRenderer(SDL_Renderer * renderer)
{
	this->renderer = renderer;
	textures["map"]		= IMG_LoadTexture(renderer, "images/xid-2600189_1.png"); 
	textures["hare"]	= IMG_LoadTexture(renderer, "images/rabbit-2.png");
	textures["cow"]		= IMG_LoadTexture(renderer, "images/cow-1.png");
	textures["pill"]	= IMG_LoadTexture(renderer, "images/pill.png");
	textures["gun"]		= IMG_LoadTexture(renderer, "images/gun-metal.png");
}

void MainVisitor::draw(std::vector<std::shared_ptr<BaseVisitiable>>& objects)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	position.x = 0;
	position.y = 0;
	position.h = 600;
	position.w = 1200;

	SDL_RenderCopy(renderer, textures["map"], NULL, &position);

	for (auto object : objects)
	{
		object->accept(this);
	}

	SDL_RenderPresent(renderer);

	nodesVisited.clear();
}


void MainVisitor::visit(GraphNode * node)
{
	SDL_SetRenderDrawColor(renderer, 100, 150, 255, SDL_ALPHA_OPAQUE);
	drawcircle(renderer, node->getX(), node->getY(), 20);
	auto edges = node->getEdges();
	//draw all edges
	for (auto edge : edges)
	{
		
		auto from	= edge->getFrom();
		auto to		= edge->getTo();

		if ( std::find(nodesVisited.cbegin(), nodesVisited.cend(), make_pair(from, to)) == nodesVisited.cend() ) // prevent dubble painting
		{
			SDL_RenderDrawLine(renderer, from->getX(), from->getY(), to->getX(), to->getY());
			nodesVisited.push_back(make_pair(from, to)); // add both combinations
			nodesVisited.push_back(make_pair(to, from));
		}
	}

	auto objects = node->getObjects();

	for (auto object : objects)
	{
		object->accept(this);
	}

	auto items = node->getItems();

	for (auto item : items)
	{
		item->accept(this);
	}
	
}

void MainVisitor::visit(CowObject * cow)
{
	position.h = 110;
	position.w = 110;
	drawObjectTexture(cow, textures["cow"], &position);
}


void MainVisitor::visit(HareObject * hare)
{
	position.w = 60;
	position.h = 60;

	drawObjectTexture(hare, textures["hare"], &position);
}

void MainVisitor::visit(PillItem * pill)
{
	position.w = 20;
	position.h = 20;

	drawObjectTexture(pill, textures["pill"], &position);
}

void MainVisitor::visit(GunItem * gun)
{
	position.w = 40;
	position.h = 40;

	drawObjectTexture(gun, textures["gun"], &position);
}

void MainVisitor::drawObjectTexture(BaseObject * object, SDL_Texture * texture, SDL_Rect * position)
{
	position->x = object->getX();
	position->y = object->getY();

	SDL_RenderCopy(renderer, texture, NULL, position);
}
