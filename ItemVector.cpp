#include "ItemVector.h"

ItemVector::ItemVector() : size(0),capacity(2) {
    data = new Item[capacity];
}

ItemVector::~ItemVector() {
    delete[] data;
}

void ItemVector::push_back(const Item& newItem) {
    if (size >= capacity) {
        capacity *= 2;
        Item* newData = new Item[capacity];
        for (int i = 0; i < size; i++) {
        newData[i] = data[i];
        } 
        delete[] data;
        data = newData;
    }  
    data[size] = newItem;
    size++;
}

Item& ItemVector::getAt(int index) const {
    if(index >= 0 && index < size) {
        return data[index];
    }
}
void ItemVector::clear() {
    delete[] data;
    capacity = 2;
    size = 0;
    data = new Item[capacity];
}