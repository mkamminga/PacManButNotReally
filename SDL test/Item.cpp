#include "Item.h"
#include "GraphNode.h" 


void Item::setNode(std::shared_ptr<GraphNode> node)
{
	if (currentNode)
	{
		currentNode->removeItem(shared_from_this());
	}

	currentNode = node;
}

const std::shared_ptr<GraphNode> Item::getNode() const
{
	return currentNode;
}

