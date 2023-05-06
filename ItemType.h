#ifndef ITEMTYPE
#define ITEMTYPE

class ItemType {
public:
    enum Line{
        START, AFTER_RETURN, AFTER_REC
    };

    int n;
    int x;
    ItemType* next = nullptr;
    Line line;

    ItemType(int n, int x, Line line);


};

#endif
