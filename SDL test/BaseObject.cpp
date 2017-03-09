#include "BaseObject.h"

const int BaseObject::getX() const
{
	return x;
}

const int BaseObject::getY() const 
{
	return y;
}

void BaseObject::setX(const int x)
{
	this->x = x;
}

void BaseObject::setY(const int y)
{
	this->y = y;
}