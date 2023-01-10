#pragma once
#include "IVisitor.h"

class IElement_Item {
public:
	virtual void accept(IVisitor* v) = 0;
	virtual double get() = 0;
};