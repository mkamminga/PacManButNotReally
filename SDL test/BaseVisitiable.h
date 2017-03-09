#pragma once
#include "BaseVisitor.h"

class BaseVisitiable {
public:
	virtual void accept(BaseVisitor*) = 0;
};