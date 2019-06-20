#include "composite.h"
#include <memory>

int main()
{
    std::unique_ptr<HTMLCompositeTag> root{new HTMLCompositeTag("html")};
    root->addComponent(new HTMLCompositeTag("body"));
    auto body = root->getComponent(0)->getComposite();
    body->addComponent(new HTMLTag("h1","Naslov"));
    body->addComponent(new HTMLCompositeTag("ol"));
    auto ol = body->getComponent(1)->getComposite();
    ol->addComponent(new HTMLTag("li", "oitem-1"));
    ol->addComponent(new HTMLTag("li", "oitem-2"));
    ol->addComponent(new HTMLTag("li", "oitem-3"));

    auto it = root->iterator();
   for(it.first(); !it.isDone(); it.next()){
       auto & xx{it.currentItem()};
       if(xx.getTagName() == "h1")
            xx.setTagName("h2");
   }
std::cout<<root->generateHTML()<<std::endl;
/*
it.first(); std::cout<<it.isDone();
//std::cout << it.currentItem().getTagName() << std::endl;
it.next(); std::cout<<it.isDone();
//std::cout << it.currentItem().getTagName() << std::endl;
it.next(); std::cout<<it.isDone();
//std::cout << it.currentItem().getTagName() << std::endl;
it.next(); std::cout<<it.isDone();
//std::cout << it.currentItem().getTagName() << std::endl;
it.next(); std::cout<<it.isDone();
//std::cout << it.currentItem().getTagName() << std::endl;
it.next(); std::cout<<it.isDone();
//std::cout << it.currentItem().getTagName() << std::endl;
it.next(); std::cout<<it.isDone();
//std::cout << it.currentItem().getTagName() << std::endl;
it.next(); std::cout<<it.isDone();*/

   // Ponovna inicijalizacija istog iteratora.
   for(it.first(); !it.isDone(); it.next()){
       auto & xx{it.currentItem()};
       //std::cout << xx.getTagName() << std::endl;
       if(xx.getTagName() == "ol"){
            xx.getComposite()->removeComponent(0);
            break;
       }
   }

   it = root->iterator(); // CCTor
   body = root->getComponent(0)->getComposite();
   ol = body->getComponent(1)->getComposite();

    return 0;
}
