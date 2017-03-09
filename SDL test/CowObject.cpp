#include "CowObject.h"
#include "PillItem.h"

void CowObject::accept(BaseVisitor* visitor)
{
	visitor->visit(this);
}

void CowObject::update()
{
	if (!currentState)
	{ 
		currentState = std::make_unique<CowWandering>(shared_from_this());
	}
	currentState->check();
	currentState->update();
}