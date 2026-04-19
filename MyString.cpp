#include "MyString.h"
#include <cstring>
#include <iostream>


MyString::MyString():length(0) {
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString (const char* str) : data(nullptr), length(0) {
        if (str && str[0] != '\0') {
            length = strlen(str);
            data = new char[length + 1];
            strcpy_s(data, length + 1, str);
        }
        else {
            data = new char[1];
            data[0] = '\0';
            length = 0;
        }
}

MyString::MyString (const MyString& other) : data(nullptr), length(other.length)
{
    if (other.data != nullptr) {
        data = new char[length + 1];
        strcpy_s(data, length + 1, other.data);
    }
    else {
        length = 0;
        data = new char[1] {'\0'};
    }
}

MyString::~MyString() {
    delete[] data;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy_s(data, length + 1, other.data);
    }
    return *this;
}

bool MyString::operator==(const MyString& other) const {
    if (!(length==other.length)) { return false; }
    return strcmp(data,other.data)==0;
}

bool MyString::operator==(const char* other) const {
    if (other == nullptr || length != strlen(other)) { return false; }
    return strcmp(data, other) == 0;
}

char& MyString::operator[](int index) {
    return data[index];//не безопасно надо ловить исключение
}

const char& MyString::operator[](int index) const {
    return data[index];
}
MyString& MyString::operator+=(char c) {
    int newLength = length + 1;
    char* newData = new char[newLength + 1];
    if (data != nullptr) {
        for (int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        delete[] data;
    }
    newData[length] = c;
    newData[newLength] = '\0';
    data = newData;
    length = newLength;
    return *this;
}
MyString& MyString::operator+=(const char* str) {
    if (str) {
        for (int i = 0; str[i] != '\0'; ++i) {
            *this += str[i];
        }
    }
    return *this;
}
MyString& MyString::operator+=(const MyString& other) {
    for (int i = 0; i < other.length; i++) {
        *this += other[i];
    }
    return *this;
}

const char* MyString::c_str() const {
    return data;
}

int MyString::size() const {
    return length;
}

bool MyString::empty() const {
    return length == 0;
}

void MyString::clear() {
    delete[] data;
    data = new char[1];
    data[0] = '\0';
    length = 0;
}
std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.data;
    return os;
}

void MyString::replace(char first, char second) {
    for (int i = 0; i < length; i++) {
        if (data[i] == '_') {
            data[i] = ' ';
        }
    }
}
