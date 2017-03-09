#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "BaseVisitor.h"
#include "BaseVisitiable.h"
#include <vector>
#include <memory>
#include <map>

class BaseObject;

class MainVisitor : public BaseVisitor
{
private:
	SDL_Renderer* renderer = nullptr;

	SDL_Rect position;
	std::map<std::string, SDL_Texture*> textures;
	std::vector< std::pair<std::shared_ptr<GraphNode>, std::shared_ptr<GraphNode>> > nodesVisited;

public:
	void setRenderer(SDL_Renderer* renderer);
	void draw(std::vector<std::shared_ptr<BaseVisitiable>>& objects);
	virtual void visit(CowObject* cow);
	virtual void visit(GraphNode* graphNode);
	virtual void visit(HareObject* hare);
	virtual void visit(PillItem* hare);
	virtual void visit(GunItem* node);
	void drawObjectTexture(BaseObject* object, SDL_Texture * texture, SDL_Rect* position);

	~MainVisitor()
	{
		for (auto texture : textures)
		{
			SDL_DestroyTexture(texture.second);
		}
	}
};

