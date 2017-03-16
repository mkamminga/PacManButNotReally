#include "PillItem.h"
#include "BaseState.h"
#include "GraphNode.h" 

void PillItem::execute(std::shared_ptr<GamePlayObject> object)
{
	
}

void PillItem::accept(BaseVisitor * bv)
{
	bv->visit(this);
}
