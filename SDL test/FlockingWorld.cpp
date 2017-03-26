#include "FlockingWorld.h"


const Dimension & FlockingWorld::getDimension() const
{
	return dimensions;
}

void FlockingWorld::addObject(std::shared_ptr<GamePlayObject> object)
{
	objects.push_back(object);

	object->setX(dimensions.x0);
	object->setY(dimensions.y0);
}

const std::vector<std::shared_ptr<GamePlayObject>>& FlockingWorld::getObjects() const
{
	return objects;
}

void FlockingWorld::clear()
{
	objects.clear();
}

void FlockingWorld::wrap(Vector2D & pos)
{
	if (!dimensions.withinBounds(pos))
	{
		pos.x = dimensions.x1 - (pos.x + dimensions.x0) + dimensions.x1;
		pos.y = dimensions.y1 - pos.y;
	}
}
