//#ifndef IVISITOR_H_
//#define IVISITOR_H_

#pragma once
#include "ConcreteElementFruit.h"
#include "ConcreteElementBook.h"
#include "ConcreteElementDvd.h"

class IVisitor {
public:
	virtual void VisitConcreteElement_Dvd(ConcreteElement_Dvd* CEA)  = 0;
	virtual void VisitConcreteElement_Fruit(ConcreteElement_Fruit* CEB) = 0;
	virtual void VisitConcreteElement_Book(ConcreteElement_Book* CEB) = 0;
};

//#endif