#pragma once
#include "MyString.h"
#ifndef STATVECTOR
#define STATVECTOR

#include <iostream>

struct StatPair {
    MyString key;
    int value;
};

struct StatVector {
    StatPair* data;
    int size;

    StatVector(int count);
    StatVector(const StatVector& other);
    ~StatVector();

    int getValue(const MyString& name) const;
    StatPair getAt(int ind) const;
    void setAt(int index, const MyString& key, int value);
    bool empty() const;

    StatVector& operator=(const StatVector& other);
};
#endif