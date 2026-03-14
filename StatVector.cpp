#include "StatVector.h"

StatVector::StatVector(int count) : size(count){
    if (size > 0) {
        data = new StatPair[size];
    }
    else {
        data = nullptr;
    }

}

StatVector::StatVector(const StatVector& other) 
    : data(nullptr), size(other.size){ 
    if (size > 0 && other.data != nullptr) {
        data = new StatPair[size];

        for (int i = 0; i < size; i++) {
            data[i].key = other.data[i].key;
            data[i].value = other.data[i].value;
        }
    }
    else {
        size = 0;
        data = nullptr;
    }
}

StatVector::~StatVector() {
	delete[] data;
}

int StatVector::getValue(const MyString& name) const {
    for (int i = 0; i < size; ++i) {
        if (data[i].key == name) {
            return data[i].value;
        }
    }
    return 0;
}

StatPair StatVector::getAt(int ind) const {
      if (ind >= 0 && ind < size) {
            return data[ind];
      }
      return { MyString("Error"), 0 };
}
void StatVector::setAt(int index, const MyString& key, int value) {
    if (index >= 0 && index < size) {
        data[index].key = key;
        data[index].value = value;
    }
}


bool StatVector::empty() const {
    return size == 0;
}

StatVector& StatVector::operator=(const StatVector& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new StatPair[size];
        for (int i = 0; i < size; i++) {
            data[i].key = other.data[i].key;
            data[i].value = other.data[i].value;
        }
    }
    else { data = nullptr; }
    return *this;
}
void StatVector::addOrUpdate(const MyString& key, int value) {
    for (int i = 0; i < size; i++) {
        if (data[i].key == key) {
            data[i].value += value;
            return;
        }
    }
    StatPair* newData = new StatPair[size + 1];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    newData[size].key = key;
    newData[size].value = value;
    delete[] data;
    data = newData;
    size++;
}
