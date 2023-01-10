#include "ConcreteElementFruit.h"
#include <iostream>
using namespace std;

void ConcreteElement_Fruit::accept(IVisitor* v) {
	cout << "Fruit calling Visitor.VisitConcreteElement_Fruit()..." << endl;
	v->VisitConcreteElement_Fruit(this);
}

void ConcreteElement_Fruit::discount() {
	cout << "Price of fruit: " << weightKg*price << "." << endl;
}