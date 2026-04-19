#pragma once

template <typename T>
struct MyVector {
    T* data;
    int size;
    int capacity;

    MyVector() : size(0), capacity(2) {
        data = new T[capacity];
    }
    MyVector(const MyVector& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    ~MyVector() {
        delete[] data;
    }
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    void push_back(const T& newItem) {
        if (size >= capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size] = newItem;
        size++;
    }
    T& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return data[0];
    }
    const T& operator[] (int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return data[0];
    }
    void clear() {
        delete[] data;
        capacity = 2;
        size = 0;
        data = new T[capacity];
    }
    int getSize() const {
        return size;
    }
};
