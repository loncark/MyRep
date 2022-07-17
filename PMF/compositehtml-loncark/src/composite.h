#pragma once

#include <string>
#include <list>
#include <stack>
#include <iostream>

class HTMLCompositeTag;
class CompositeIterator;

// Component klasa.
class HTMLComponent
{
public:
    virtual ~HTMLComponent() {}

    //izvođenje funkcije u Composite klasi vodi do kontradikcije s primjerom!
    virtual HTMLCompositeTag* getComposite() {return NULL;}

    virtual std::string getTagName() = 0;
    virtual void setTagName(std::string s) = 0;
    virtual std::string getStartTag() = 0;
    virtual std::string getEndTag() = 0;
    virtual std::string getBody() = 0;
    virtual void setBody(std::string s) = 0;
    virtual std::string generateHTML() = 0;

    //mora biti ovdje jer postoji mogućnost da prvi poziv bude na ne-Composite objektu
    virtual CompositeIterator iterator() = 0;
};

// Klasa jednog taga
class HTMLTag : public HTMLComponent{
public:
    HTMLTag(std::string const& tag, std::string const& body);

    std::string getTagName() {return mTagName;}
    void setTagName(std::string s) {mTagName=s;}
    std::string getStartTag() {return "<"+mTagName+">";}
    std::string getEndTag() {return "</"+mTagName+">";}
    std::string getBody() {return mBody;}
    void setBody(std::string s) {mBody=s;}
    std::string generateHTML()
        {return getStartTag()+getBody()+getEndTag();}
    CompositeIterator iterator();
private:
    std::string mTagName;
    std::string mBody;
};

// Tekst između manjih tagova u Composite klasi
class HTMLText : public HTMLComponent{
public:
    HTMLText(std::string const& text);

    std::string getTagName() {return mTagName;}
    void setTagName(std::string s) {mTagName=s;}
    std::string getStartTag() {return "<"+mTagName+">";}
    std::string getEndTag() {return "<"+mTagName+"/>";}
    std::string getBody() {return mBody;}
    void setBody(std::string s) {mBody=s;}
    std::string generateHTML()
        {return getStartTag()+getBody()+getEndTag();}
    CompositeIterator iterator();
private:
    std::string mBody;
    std::string mTagName="text";
};

// Composite klasa
class HTMLCompositeTag : public HTMLComponent{
public: 
    HTMLCompositeTag* getComposite() {return this;}
    std::string getTagName() {return mTagName;}
    void setTagName(std::string s) {mTagName=s;}
    std::string getStartTag() {return "<"+mTagName+">";}
    std::string getEndTag() {return "</"+mTagName+">";}
    std::string getBody();
    void setBody(std::string s) {}
    std::string generateHTML()
        {return getStartTag()+getBody()+getEndTag();}
    CompositeIterator iterator();

    HTMLCompositeTag(std::string const& s);
    ~HTMLCompositeTag();
    void addComponent(HTMLComponent* cmp);
    void removeComponent(std::size_t index);
    HTMLComponent* getComponent(std::size_t index);
    HTMLComponent* getLastComponent() {return getComponent(mChildren.size()-1);}
private:
    std::list<HTMLComponent*> mChildren;
    std::string mTagName;

    friend class CompositeIterator;
    friend class HTMLComponent;
};


class Iterator
{
public:
    Iterator() {}
    virtual ~Iterator() {}

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual HTMLComponent& currentItem() const = 0;
    virtual HTMLComponent* currentPointer() const = 0;
};


class CompositeIterator : public Iterator{
public:
    CompositeIterator() : Iterator() {}
    ~CompositeIterator() {}

    void first();
    void next();
    bool isDone();
    HTMLComponent& currentItem() const;
    HTMLComponent* currentPointer() const;
    bool mItPokazujeNaCTag();
    int stackSize() {return mStack.size();}
private:
    HTMLCompositeTag* mCaller;
    std::list<HTMLComponent*>::iterator mIt;
    std::stack<std::list<HTMLComponent*>::iterator> mStack;
    //čuva pointere na CompositeTag po kojem trenutno iteriramo

    bool prvi=true;
    friend class HTMLCompositeTag;
};

