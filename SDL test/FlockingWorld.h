#pragma once
#include <vector>
#include <memory>

#include "GamePlayObject.h"
#include "Dimensions.h"
#include "Vector2D.h"

class FlockingWorld
{
private:
	std::vector<std::shared_ptr<GamePlayObject>> objects;
	Dimension dimensions;
public:
	FlockingWorld(const Dimension& d) :  dimensions(d) {}
	const Dimension& getDimension() const;
	void addObject(std::shared_ptr<GamePlayObject>);
	const std::vector<std::shared_ptr<GamePlayObject>>& getObjects() const;
	void clear();
	void wrap(Vector2D& pos);
};

