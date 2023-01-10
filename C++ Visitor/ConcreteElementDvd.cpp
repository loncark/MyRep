#include "ConcreteElementDvd.h"
#include <iostream>
using namespace std;

void ConcreteElement_Dvd::accept(IVisitor* v) {
	cout << "Dvd calling Visitor.VisitConcreteElement_Dvd()..." << endl;
	v->VisitConcreteElement_Dvd(this);
}

void ConcreteElement_Dvd::discount() {
	cout << "Discounted Dvd from " << price << " to ";
	if (price > 20) price -= 5;
	else if (region == 2) price -= 2;
	cout << price << "." << endl;
}