#include "MainVisitor.h"
#include "BaseObject.h"
#include "GraphNode.h"
#include "NodeEdge.h"
#include "SparseGraph.h"
#include "PillItem.h"
#include "GhostObject.h"
#include "PacManObject.h"

void MainVisitor::setRenderer(SDL_Renderer * renderer)
{
	this->renderer = renderer;
	textures["map"]		= IMG_LoadTexture(renderer, "images/xid-2600189_1.png"); 
	textures["pill"]	= IMG_LoadTexture(renderer, "images/pill.png");
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

void MainVisitor::visit(PillItem * pill)
{
	position.w = 20;
	position.h = 20;

	drawObjectTexture(pill, textures["pill"], &position);
}

void MainVisitor::visit(GhostObject * ghost)
{
	position.w = 20;
	position.h = 20;

	drawObjectTexture(ghost, textures["pill"], &position);
}

void MainVisitor::visit(PacManObject * pacman)
{
	position.w = 20;
	position.h = 20;

	drawObjectTexture(pacman, textures["pill"], &position);
}


void MainVisitor::drawObjectTexture(BaseObject * object, SDL_Texture * texture, SDL_Rect * position)
{
	position->x = object->getX();
	position->y = object->getY();

	SDL_RenderCopy(renderer, texture, NULL, position);
}
