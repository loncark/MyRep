//#ifndef CONCRETEELEMENTFRUIT_H
//#define CONCRETEELEMENTFRUIT_H

#pragma once
#include "IVisitor.h"
#include "IElementItem.h"

class ConcreteElement_Fruit : public IElement_Item {
public:
	virtual void accept(IVisitor* v) override;
	void discount();
	double get() override { return price; }
private:
	double weightKg = 2.5;
	double price = 15.0;
};

//#endif