#include "MainVisitor.h"
#include "BaseObject.h"
#include "GraphNode.h"
#include "NodeEdge.h"
#include "SparseGraph.h"
#include "PillItem.h"
#include "GhostObject.h"
#include "PacManObject.h"
#include "GhostWanderingState.h"
#include "GhostChasingState.h"
#include "GhostChasingPillState.h"
#include <memory>


void MainVisitor::setRenderer(SDL_Renderer * renderer)
{
	fastButton.setRender(renderer);
	fastButton.setPosition(1000, 50);
	this->renderer = renderer;
	textures["map"]							= IMG_LoadTexture(renderer, "images/xid-2600189_1.png"); 
	textures["pacman"]						= IMG_LoadTexture(renderer, "images/xid-2600194_1.png"); 
	textures["ghost_wandering"]				= IMG_LoadTexture(renderer, "images/xid-2600193_1.png");
	textures["ghost_chasing"]				= IMG_LoadTexture(renderer, "images/xid-2600191_1.png");
	textures["ghost_pillhunting"]			= IMG_LoadTexture(renderer, "images/xid-2600192_1.png");
	textures["ghost_afterlife"]				= IMG_LoadTexture(renderer, "images/xid-2600190_1.png");
	textures["pill"]						= IMG_LoadTexture(renderer, "images/pill.png");
}

void MainVisitor::draw(std::vector<std::shared_ptr<BaseVisitiable>>& nodes, std::vector<std::shared_ptr<GamePlayObject>>& objects)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	position.x = 0;
	position.y = 0;
	position.h = 600;
	position.w = 1200;

	SDL_RenderCopy(renderer, textures["map"], NULL, &position);

	for (auto node : nodes) // draw nodes
	{
		node->accept(this);
	}

	for (auto object : objects) // draw objects
	{
		object->accept(this);
	}

	fastButton.draw();

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


void MainVisitor::visit(PacManObject * pacman)
{
	position.w = 35;
	position.h = 35;

	drawObjectTexture(pacman, textures["pacman"], &position);
}

void MainVisitor::visit(GhostWanderingState * ghostWandering, BaseObject * bo)
{
	position.w = 35;
	position.h = 35;

	drawObjectTexture(bo, textures["ghost_wandering"], &position);
}

void MainVisitor::visit(GhostChasingState * ghostChasing, BaseObject * bo)
{
	position.w = 35;
	position.h = 35;

	drawObjectTexture(bo, textures["ghost_chasing"], &position);
}

void MainVisitor::visit(GhostChasingPillState * ghostWandering, BaseObject * bo)
{
	position.w = 35;
	position.h = 35;

	drawObjectTexture(bo, textures["ghost_pillhunting"], &position);
}

void MainVisitor::visit(GhostFlockingState * ghostWandering, BaseObject * bo)
{
	position.w = 50;
	position.h = 50;

	drawObjectTexture(bo, textures["ghost_afterlife"], &position);
}


void MainVisitor::drawObjectTexture(BaseObject * object, SDL_Texture * texture, SDL_Rect * position)
{
	position->x = (object->getX() - (position->w / 2));
	position->y = (object->getY() - (position->h / 2));

	SDL_RenderCopy(renderer, texture, NULL, position);
}

void MainVisitor::listenForEvents(SDL_Event & SDLEvent)
{
	while (SDLEvent.type != SDL_QUIT) { // waiting for events to happen

		while (SDL_PollEvent(&SDLEvent)) {
			if (SDLEvent.type == SDL_MOUSEBUTTONUP)
			{
				auto x = SDLEvent.button.x;
				auto y = SDLEvent.button.y;
				//Has the button been clicked
				if (fastButton.hasBeenClicked(x, y)) {
					return;
				}
			}
		}
	}
}
