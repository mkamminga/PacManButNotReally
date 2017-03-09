#include "PillItem.h"
#include "BaseState.h"
#include "GraphNode.h" 

void PillItem::execute(std::shared_ptr<GamePlayObject> object)
{
	object->setAlertness(100);
}

void PillItem::accept(BaseVisitor * bv)
{
	bv->visit(this);
}
