#include "composite.h"
#include <iostream>
#include <typeinfo>

HTMLCompositeTag::~HTMLCompositeTag()
{
    for(auto it=0; it!=mChildren.size(); ++it)
        delete getComponent(it);
}

//HTMLTag konstruktor
HTMLTag::HTMLTag(std::string const& tag, std::string const& body)
    : mTagName(tag), mBody(body) {}

CompositeIterator HTMLTag::iterator()
{
    CompositeIterator It; return It;
}

//HTMLText konstruktor
HTMLText::HTMLText(std::string const& text) : mBody(text) {}

CompositeIterator HTMLText::iterator()
{
    CompositeIterator It; return It;
}

CompositeIterator HTMLCompositeTag::iterator()
{
    CompositeIterator It;
    It.mCaller=this;
    It.mIt=this->mChildren.begin();
    //mIt je LIST ITERATOR!!!
    return It;
}

//HTMLCompositeTag konstruktor
HTMLCompositeTag::HTMLCompositeTag(const std::string &s)
    : mTagName(s) {}

void HTMLCompositeTag::addComponent(HTMLComponent *cmp)
{
    mChildren.insert(mChildren.end(), cmp);
}

void HTMLCompositeTag::removeComponent(std::size_t index)
{
    auto it=mChildren.begin();
    for(int i=0; i<index; ++i) {++it;}
    if(*it!=NULL) delete(*it);
    mChildren.erase(it);
}

//vraća pointer na i-ti HTMLComponent
HTMLComponent* HTMLCompositeTag::getComponent(std::size_t index)
{
    auto it=mChildren.begin();
    for(int i=0; i<index; ++i) {++it;}
    return *it;
}

std::string HTMLCompositeTag::getBody()
{
    std::string stranica;
    for(auto it=mChildren.begin(); it!=mChildren.end(); ++it)
        {
            //std::cout<<it.currentItem().getStartTag()<<std::endl;
            stranica+=(*it)->generateHTML();
        }
    return stranica;
}

//iterator
HTMLComponent& CompositeIterator::currentItem() const
{
    //zato što root nije dio nikakve liste:
    if(prvi) return *mCaller;
    return **mIt;
}

HTMLComponent* CompositeIterator::currentPointer() const
{
    //zato što root nije dio nikakve liste:
    if(prvi) return mCaller;
    return *mIt;
}

//postavlja mIt na prvu podkomponentu pozivatelja
void CompositeIterator::first()
{
    prvi=true; while(!mStack.empty()) mStack.pop();
}

void CompositeIterator::next()
{
    if(prvi)
        {
            prvi=false;
            mIt=mCaller->mChildren.begin();
            mStack.push(mIt);
            mStack.push(mCaller->mChildren.end());
            return;
        }
    if((*mIt)->getComposite()!=NULL)
        {
            mStack.push(mIt);
            mStack.push((*mIt)->getComposite()->mChildren.end());
            mIt=(*mIt)->getComposite()->mChildren.begin();
        }
     else ++mIt;
    while(mIt==mStack.top())
        {
            mStack.pop();
            mIt=mStack.top();
            ++mIt;
            mStack.pop();
            if(stackSize()==0) break;
        }
}

bool CompositeIterator::isDone()
{
    if(stackSize()==0 && prvi==false) return true;
    return false;
}
