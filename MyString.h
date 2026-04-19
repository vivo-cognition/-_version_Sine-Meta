#pragma once
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
    MyString& operator+=(char c);
    MyString& operator+=(const char* str);
    MyString& operator+=(const MyString& other);


    const char* c_str() const;
    int size() const;
    bool empty() const;
    void clear();
    void replace(char first, char second);


    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
};
