//#ifndef CONCRETEELEMENTDVD_H
//#define CONCRETEELEMENTDVD_H

#pragma once
#include "IVisitor.h"
#include "IElementItem.h"

class ConcreteElement_Dvd : public IElement_Item {
public:
	void accept(IVisitor* v) {};
	void discount();
	double get() { return price; };
private:
	int region = 2;
	double price = 25;
};

//#endif