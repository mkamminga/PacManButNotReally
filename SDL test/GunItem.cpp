#include "GunItem.h"


void GunItem::execute(std::shared_ptr<GamePlayObject> object)
{
	object->setAttack(object->getAttack() + 10);
}

void GunItem::accept(BaseVisitor * bv)
{
	bv->visit(this);
}
