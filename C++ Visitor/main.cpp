#include<iostream>
#include<list>
#include "IElementItem.h"
#include "IVisitor.h"
#include "ConcreteElementDvd.h"
#include "ConcreteElementBook.h"
#include "ConcreteElementFruit.h"
#include <iterator>
using namespace std;

class Discount_Visitor : public IVisitor {
public:
	void VisitConcreteElement_Dvd(ConcreteElement_Dvd* CEA) override{
		cout << "Visitor calling Dvd.discount()...";
		CEA->discount();
	};
	void VisitConcreteElement_Fruit(ConcreteElement_Fruit* CEB) override {
		cout << "Visitor calling Fruit.discount()...";
		CEB->discount();
	};
	void VisitConcreteElement_Book(ConcreteElement_Book* CEB) override {
		cout << "Visitor calling Book.discount()...";
		CEB->discount();
	};
};

class ObjectStructure_ShoppingCart {
public:
	double calculate(IVisitor* v) {
		list<IElement_Item>::iterator i;
		double sum = 0;
		for (i = items.begin(); i != items.end(); ++i) {
			i->accept(v);
			sum += i->get();
		}
		return sum;
	};
	void add(IElement_Item* el) {
		items.push_back(*el);
	}
private:
	list<IElement_Item> items;
};

int main() {
	/*ObjectStructure_ShoppingCart obj;
	Discount_Visitor vis1;

	ConcreteElement_Dvd ced;
	ConcreteElement_Fruit cef;
	ConcreteElement_Book ceb;*/

	//obj.add(&ced);
	//obj.add(&cef);
	//obj.add(&ceb);

	//cout << "Total price: " << obj.calculate(&vis1) << endl;

	return 0;
}