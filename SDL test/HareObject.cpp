#include "HareObject.h"

void HareObject::accept(BaseVisitor * base)
{
	base->visit(this);
}

void HareObject::update()
{
	//do nothing, for now
}
