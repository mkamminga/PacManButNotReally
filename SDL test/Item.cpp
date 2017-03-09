#include "Item.h"
#include "GraphNode.h" 


void Item::setNode(std::shared_ptr<GraphNode> node)
{
	std::shared_ptr<GamePlayObject> object;

	if (currentNode)
	{
		currentNode->removeItem(shared_from_this());
	}

	currentNode = node;
}

std::shared_ptr<GraphNode> Item::getNode()
{
	return currentNode;
}

