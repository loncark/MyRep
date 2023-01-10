#include "ConcreteElementBook.h"
#include <iostream>
using namespace std;

void ConcreteElement_Book::accept(IVisitor* v) {
	cout << "ConcreteElement_Book calling Visitor.VisitConcreteElement_Book()..." << endl;
	v->VisitConcreteElement_Book(this);
}

void ConcreteElement_Book::discount() {
	cout << "Discounted Book from " << price << " to ";
	if (price > 35) price -= 10;
	cout << price << "." << endl;
}