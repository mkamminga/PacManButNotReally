#pragma once
#include "BaseVisitiable.h"
#include <memory>

class GraphNode;

class BaseObject :  public BaseVisitiable
{
protected:
	int x = 0;
	int y = 0;

public:
	BaseObject(int x, int y) : x(x), y(y) {}

	const int getX() const;
	const int getY() const;

	void setX(const int x);
	void setY(const int y);
};

