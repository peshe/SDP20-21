#ifndef STACK
#define STACK

#include <iostream>
using namespace std;

template<typename T>
class Stack {
    static const int startCap = 10;

    int size;
    int capacity;
    T* data;

    void copyData(const Stack& other) {
        clearData();
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for(int i = 0; i< size; ++i) {
            data[i] = other.data[i];
        }
    }

    void clearData() {
        delete [] data;
    }

    void resize(int newCapacity) {
        if(newCapacity < size) {
            throw "error";
        }

        T* tempArr = new T[newCapacity];
        for(int i = 0; i< size; ++i) {
            tempArr[i] = data[i];
        }
        clearData();
        data = tempArr;
        capacity = newCapacity;
    }

public:

    Stack(): size(0), capacity(startCap), data(new T[startCap]) {}
    Stack(const Stack& other): size(other.size), capacity(other.capacity), data(NULL) {
        copyData(other);
    }
    const Stack& operator=(const Stack& other) {
        if(this != &other) {
            copyData(other);
        }
        return *this;
    }
    ~Stack() {
        clearData();
    }

    int getSize() {
        return size;
    }

    void push_back(T element) {
        if(size >= capacity) {
            resize(capacity*2);
        }
        data[size++] = element;
    }

    void pop_back() {
        if(size-1 < capacity/2 && capacity > startCap) {
            resize(capacity/2);
        }

        --size;
    }

    const T& top() {
        if(size < 1) {
            throw "stack is empty";
        }

        return data[size-1];
    }

    bool empty() const {
        return size == 0;
    }
};

#endif // STACK
