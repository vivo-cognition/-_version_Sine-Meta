#include "MyString.h"

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

//операторы
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
//функции
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