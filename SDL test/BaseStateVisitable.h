#pragma once
#include "BaseVisitor.h"

class BaseStateVisitiable {
public:
	virtual void accept(BaseVisitor*, BaseObject* ) = 0;
};