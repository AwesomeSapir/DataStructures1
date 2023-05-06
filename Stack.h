#ifndef STACK
#define STACK

#include "ItemType.h"

class Stack {
private:
    ItemType* top = nullptr;

public:
    bool isEmpty() { return top == nullptr; }
    void makeEmpty();
    void push(ItemType item);
    ItemType pop();
};

#endif
