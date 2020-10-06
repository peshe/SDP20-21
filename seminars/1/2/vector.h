#ifndef VECTOR
#define VECTOR

#include <iostream>
using namespace std;

template<typename T>
class Vector {
    static const int startCap = 10;

    int size;
    int capacity;
    T* data;

    void copyData(const Vector& other) {
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
    Vector(): size(0), capacity(startCap), data(new T[startCap]) {}
    Vector(const Vector& other): size(other.size), capacity(other.capacity), data(NULL) {
        copyData(other);
    }
    const Vector& operator=(const Vector& other) {
        if(this != &other) {
            copyData(other);
        }
        return *this;
    }
    ~Vector() {
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

    void insert(T element, int index) {
        if(size >= capacity) {
            resize(capacity*2);
        }

        for(int i = size; i > index; --i) {
            data[i] = data[i-1];
        }
        data[index] = element;
        ++size;
    }

    void delete_at(int index) {
        for(int i = index+1; i< size; ++i) {
            data[i-1] = data[i];
        }

        if(size < capacity/2 && capacity > startCap) {
            resize(capacity/2);
        }

        --size;
    }

    void print() {
        for(int i = 0; i< size; ++i) {
            cout<< data[i]<< " ";
        }
        cout<< endl;
    }

    int findElement(T element) {
        for(int i = 0; i< size; ++i) {
            if(data[i] == element) {
                return i;
            }
        }
        return -1;
    }

    T& at(int index) {
        if(index < 0 || index > size) {
            throw "out of range";
        }

        return data[index];
    }

    T& operator[](int index) {
        return at(index);
    }

    void swap(int i, int j) {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    void reverse(int a, int b) {
        int revSize = b-a;
        for(int i = 0; i< revSize/2; ++i) {
            swap(a + i, b - i);
        }
    }
};

#endif // VECTOR
