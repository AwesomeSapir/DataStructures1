#pragma once

class ItemType {
public:
    enum Line{
        START, AFTER_RETURN, AFTER_REC
    };

    int index;
    int compared;
    ItemType* next = nullptr;
    Line line;

    ItemType(int n, int x, Line line);

};
