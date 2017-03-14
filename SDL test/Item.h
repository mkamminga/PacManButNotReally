#pragma once

#include "BaseObject.h" 
#include "GamePlayObject.h"

class Item : public BaseObject, public std::enable_shared_from_this<Item>
{
protected:
	std::shared_ptr<GraphNode> currentNode = nullptr;

public:
	Item() : BaseObject(0,0) {}
	virtual void setNode(std::shared_ptr<GraphNode> node);
	const std::shared_ptr<GraphNode> getNode() const;
	virtual void execute(std::shared_ptr<GamePlayObject>) = 0;
};

