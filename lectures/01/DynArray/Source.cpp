/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for dynamic array.
* 
* A main test file
*
* (cc) Petar Armyanov, FMI, 2020
*******************************************************************/

#include "dynArray.h"
#include <iostream>

using std::endl;
using std::cout;

using namespace fmi::sdp;

int main()
{
// test the constructors
    DynArray<int> intArray;
    DynArray<short> shortArray(3);


// test addition
    for (int i = 0; i < 10; ++i) {
        intArray.append(i);
    }

// test the inner iterator class
    for (DynArray<int>::DArrayIterator it = intArray.begin(); it != intArray.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (const int& val : intArray) {
        cout << val << " ";
    }
    cout << endl;

// test the += operator with a single element
    for (short i = 100; i < 120; ++i) {
        shortArray += i;
    }

// assign values from array with different type 
    intArray = shortArray;
    for (DynArray<int>::DArrayIterator it = intArray.begin(); it != intArray.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;


// append different types
    intArray += shortArray;
    for (size_t i = 0; i < intArray.getSize(); ++i) {
        // test the operator []
        cout << intArray[i] << " ";
    }
    cout << endl;

// test the clear method
    intArray.clear();
    assert(intArray.isEmpty());

// copy ctor test with different types
    DynArray<float> testArray(shortArray);
    cout << testArray[5] << endl;

// test search and remove
    assert(shortArray.contains(111));
    shortArray.remove(11);
    assert(!shortArray.contains(111));

    for (size_t i = 0; i < shortArray.getSize(); ++i) {
        cout << shortArray.get(i) << " ";
    }
    cout << endl;

// copy ctor with same type and operator + with different types
    DynArray<int> big = intArray + shortArray;
    cout << big.getSize() << endl;

    big += 'a';
    cout << big[big.getSize() - 1] << endl;

// assignment the same types
    intArray = big;
    cout << intArray[big.getSize() - 1] << endl;
    cout << big[big.getSize() - 1] << endl;

    return 0;
}
