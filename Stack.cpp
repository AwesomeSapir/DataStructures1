#include "Stack.h"

void Stack::push(ItemType item) {
    item.next = top;
    top = new ItemType(item);
}

ItemType Stack::pop(){
    ItemType res = *top;
    top = top->next;
    res.next = nullptr;
    return res;
}

void Stack::makeEmpty() {
    ItemType* curr = top;
    while (curr!= nullptr){
        top = curr->next;
        delete curr;
        curr = top;
    }
}
