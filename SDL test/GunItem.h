#pragma once
#include "Item.h"
class GunItem :
	public Item
{
public:
	virtual void execute(std::shared_ptr<GamePlayObject> object);
	virtual void accept(BaseVisitor*);
};

