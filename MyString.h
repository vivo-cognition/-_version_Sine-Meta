#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

struct MyString {
    char* data;
    int length;

    MyString();
    MyString(const char* str);
    MyString(const MyString& other);

    ~MyString();

    MyString& operator=(const MyString& other);
    bool operator==(const MyString& other) const;
    bool operator==(const char* other) const;
    char& operator[](int index);
    const char& operator[](int index) const;

    const char* c_str() const;
    int size() const;
    bool empty() const;
    void clear();

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
};



#endif