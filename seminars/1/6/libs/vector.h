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

    class Iterator {
        const T* data;
        int index;
    public:
        Iterator(const T* data, int index) : data(data), index(index) {}

        int operator++() {
            return ++index;
        }

        int operator++(int) {
            int oldIndex = index;
            index++;
            return oldIndex;
        }

        bool operator==(const Iterator& other) const {
            return index == other.index;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        const T& operator*() {
            return data[index];
        }
    };

    Iterator begin() {
        return Iterator(data, 0);
    }

    Iterator end() {
        return Iterator(data, size);
    }

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

    int getSize() const {
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

    void pop_front() {
        --size;
        for(int i = 0; i< size; ++i) {
            data[i] = data[i+1];
        }
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

    T& at(int index) {
        if(index < 0 || index > size) {
            throw "out of range";
        }

        return data[index];
    }

    T& operator[](int index) {
        return at(index);
    }

    void clear() {
        clearData();
        size = 0;
    }
};

#endif // VECTOR
