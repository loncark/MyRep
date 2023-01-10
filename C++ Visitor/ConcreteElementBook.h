//#ifndef CONCRETEELEMENTBOOK_H
//#define CONCRETEELEMENTBOOK_H

#pragma once
#include "IVisitor.h"
#include "IElementItem.h"
#include <iostream>

class ConcreteElement_Book : public IElement_Item {
public:
	void accept(IVisitor* v) override;
	void discount();
	double get() override { return price; }
private:
	std::string isbn = "book";
	double price = 40.25;
};

//#endif