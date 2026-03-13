#pragma once
#include "Item.h"
#ifndef ITEMVECTOR
#define ITEMVECTOR

struct ItemVector {
    Item* data;
    int size;
    int capacity;

    ItemVector();
    ItemVector(const ItemVector& other);
    ~ItemVector();

    void push_back(const Item& newItem);
    Item& getAt(int index) const;
    void clear();
    int getSize() const;

    ItemVector& operator=(const ItemVector& other);
};

#endif