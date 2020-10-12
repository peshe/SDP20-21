
#include <iostream>

#include <vector>
#include "dynamic_array.hpp"

using namespace dsa;

void initVector( dynamic_array<int>& vector )
{
    std::cout << "Push back 6 elements: " << std::endl;
    vector.push_back( 1 );
    vector.push_back( 2 );
    vector.push_back( 3 );
    vector.push_back( 4 );
    vector.push_back( 5 );
    vector.push_back( 6 );
}

struct Student
{
    std::string name;
    unsigned int fn;
    Student( const std::string& new_name = "", unsigned int new_fn = 0) : name( new_name ), fn( new_fn ) { }

    void print()
    {
        std::cout << "Name: " << name << ", FN: " << fn << std::endl;
    }
};

void initVectorWithStudents( dynamic_array<Student>& vector )
{
    std::cout << "Push back 6 elements: " << std::endl;
    vector.push_back( Student( "Pesho", 45623 ) );
    vector.push_back( Student( "Gosho", 45677 ) );
    vector.push_back( Student( "Yasen", 45460 ) );
    vector.push_back( Student( "Aleks", 45485 ) );
    vector.push_back( Student( "Stancho", 45921 ) );
    vector.push_back( Student( "Petka", 45321 ) );
}

void testConstuctorsAndOparatorEquals()
{
    std::cout << "----------------------TEST CONSTUCTORS AND OPERATOR EQUALS VECTOR---------------------------------\n\n";
    std::cout << "Init with default constructor:";
    dynamic_array<int> v1;
    v1.printElements( std::cout );
    v1.printInfo( std::cout );

    std::cout << "------------------------------------------------------------------------" << std::endl << std::endl;
    std::cout << "Init with capacity constructor of 16 elements:";
    dynamic_array<int> v2( 16 );
    v2.printElements( std::cout );
    v2.printInfo( std::cout );

    std::cout << "------------------------------------------------------------------------" << std::endl << std::endl;
    std::cout << "Init with capacity constructor of 5 elements and default values 37:";
    dynamic_array<int> v3( 5, 37 );
    v3.printElements( std::cout );
    v3.printInfo( std::cout );

    std::cout << "------------------------------------------------------------------------" << std::endl << std::endl;
    std::cout << "Init with initializer list:";
    dynamic_array<int> v4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    v4.printElements( std::cout );
    v4.printInfo( std::cout );

    std::cout << "------------------------------------------------------------------------" << std::endl << std::endl;
    std::cout << "Init with default constructor and use operator=():";
    dynamic_array<int> v5;
    v5 = v4;
    v5.printElements( std::cout );
    v5.printInfo( std::cout );

    std::cout << "------------------------------------------------------------------------" << std::endl << std::endl;
    std::cout << "Init with copy constructor:";
    dynamic_array<int> v6 = v4;
    v6.printElements( std::cout );
    v6.printInfo( std::cout );


    std::cout << "----------------------END TEST CONSTUCTORS AND OPERATOR EQUALS VECTOR---------------------------------\n\n";
}




void testIterasionThoughVector()
{
    std::cout << "----------------------TEST ITERASIONS THOUGH VECTOR---------------------------------\n\n";
    dynamic_array<int> myV;
    initVector( myV );

    std::cout << "Using operator[] of the dynamic array: ";
    for ( size_t i = 0; i < myV.size(); ++i )
    {
        std::cout << myV[ i ] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Using iterator of the dynamic array: ";
    for ( dynamic_array<int>::iterator iter = myV.begin(); iter != myV.end(); ++iter )
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::cout << "Using range based for loop for iterate forward through dynamic array: ";
    for ( int it : myV )            // <=> for( dynamic_array<int>::iterator iter = myV.begin(); iter != myV.end(); ++iter ) // http://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/language/range-for.html
    {                               //{          
                                    //      int it = *iter;
        std::cout << it << " ";     //      std::cout << it << " ";
    }                               //}          
    
    std::cout << std::endl;


    std::cout << "----------------------END TEST ITERASIONS THOUGH VECTOR---------------------------------\n\n";
}


void testIteratorInVector()
{

    std::cout << "----------------------TEST ITERATORS---------------------------------\n\n";
    dynamic_array<int> myV;
    initVector( myV );

    dynamic_array<int>::iterator beginIt = myV.begin();
    dynamic_array<int>::iterator endIt = myV.end();
    //const dynamic_array<int>::iterator it = myV.begin(); // we should discuss those
    //dynamic_array<int>::iterator it = myV.cbegin();

    std::cout << "Value of begin is: " << *beginIt << std::endl; // use operator*
    std::cout << "Value of end is: " << *endIt << std::endl; // use operator* // Opsss....
    std::cout << "Value of real end is: " << *( endIt - 1 ) << std::endl; // first use operator-() and second use operator*

    dynamic_array<int>::iterator secondIt = ++beginIt;
    // lets compare it
    if ( secondIt == beginIt )
    {
        std::cout << "Iterators are equal" << std::endl;
    }
    else
    {
        std::cout << "Iterators are different" << std::endl;
    }

    if ( secondIt > endIt )
    {
        std::cout << "Second iterator is greater than end iterator" << std::endl;
    }
    else
    {
        std::cout << "Second iterator is less or equal than end iterator" << std::endl;
    }

    --endIt;
    std::cout << "End iterator is now real end: " << *endIt << std::endl;

    beginIt += 2; // += with offset
    std::cout << "Value of beginIt is: " << *beginIt << std::endl; // should be 4?
    
    beginIt = myV.begin();
    std::cout << "The third element after the begining is: " << beginIt[ 3 ] << std::endl; // no make sense for me, bit it's work :/

    dynamic_array<Student> group;
    initVectorWithStudents( group );

    for ( dynamic_array<Student>::iterator s = group.begin(); s != group.end(); ++s )
    {
        s->print(); // operator->
    }


    std::cout << "----------------------END TEST ITERATORS---------------------------------\n\n";
}

void testPushBack()
{
    std::cout << "----------------------TEST PUSH BACK IN VECTOR-----------------------------\n\n";

    dynamic_array<int> myV;
    myV.printInfo( std::cout );

    initVector( myV );

    myV.printInfo( std::cout );
    myV.printElements(std::cout);

    std::cout << "----------------------END TEST PUSH BACK IN VECTOR-------------------------\n\n";
}

void testRandomAccess()
{
    std::cout << "----------------------TEST RANDOM ACCESS IN VECTOR-----------------------------\n\n";
    dynamic_array<int> vec;
    initVector( vec );
    vec.printInfo( std::cout );

    std::cout << "Front is: " << vec.front() << std::endl;
    vec.front() = 37;
    std::cout << "And now front is: " << vec.front() << std::endl;
    // same is with back() :)
    //...

    std::cout << "Element at index 4 is: " << vec.at( 4 ) << std::endl;
    vec.at( 4 ) = -42;
    std::cout << "Element at index 4 is: " << vec[ 4 ] << std::endl;

    try
    {
        vec[ 100 ] = 100;
    }
    catch ( const std::exception& e )
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "----------------------END TEST RANDOM ACCESS IN VECTOR-----------------------------\n\n";
}

void testShrinkToFit()
{
    std::cout << "----------------------TEST SHRINKING VECTOR-----------------------------\n\n";
    dynamic_array<int> vec;
    initVector( vec );
    vec.printInfo( std::cout );
    std::cout << "Shrink vector..." << std::endl;
    vec.shrink_to_fit();

    vec.printInfo( std::cout );

    std::cout << "----------------------END TEST SHRINKING VECTOR-----------------------------\n\n";
}

void testInsertionInVector()
{
    std::cout << "----------------------TEST INSERT IN VECTOR-----------------------------\n\n";
    dynamic_array<int> vec;
    initVector( vec );
    vec.printElements( std::cout );
    std::cout << "Insert 37 somewhere in the middle..." << std::endl;
    dynamic_array<int>::iterator mid = vec.insert( vec.begin() + 3, 37 );
    mid = vec.insert( vec.begin(), 39 );
    mid = vec.insert( vec.end() - 1, 42 );
    vec.insert( mid, 0 );

    vec.printElements( std::cout );
    std::cout << "----------------------END TEST INSERT IN VECTOR-----------------------------\n\n";
}

void testEraseFromVector()
{
    std::cout << "----------------------TEST ERASE FROM VECTOR-----------------------------\n\n";
    dynamic_array<int> vec;
    initVector( vec );
    vec.printElements( std::cout );
    std::cout << "Erase [3] from vector...\n";
    dynamic_array<int>::iterator next = vec.erase( vec.begin() + 2 );
    std::cout << "Next element is:" << *next << std::endl;
    vec.printElements( std::cout );

    std::cout << "------------------------------------------------------------------------\n\n";
    dynamic_array<int> v;
    initVector( v );
    v.printElements( std::cout );
    std::cout << "Erase [3, 4] from vector...\n";
    next = v.erase( v.begin() + 2, v.begin() + 4 );
    std::cout << "Next element is:" << *next << std::endl;
    v.printElements( std::cout );

    // same as erasing from std::vector :)
    std::cout << "------------------------------------------------------------------------\n\n";
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
    for ( int el : v1 ) { std::cout << el << " "; }
    std::cout << "\nErase [3, 4] from std::vector...\n";
    std::vector<int>::iterator nextEl = v1.erase( v1.begin() + 2, v1.begin() + 4 );
    std::cout << "Next element is:" << *nextEl << std::endl;
    for ( int el : v1 ) { std::cout << el << " "; }
    std::cout << std::endl;

    std::cout << "----------------------END TEST ERASE FROM VECTOR-------------------------\n\n";
}

void testSwapVectors()
{
    std::cout << "----------------------TEST SWAP TWO VECTORS-----------------------------\n\n";
    dynamic_array<int> vec1 = { 1, 2, 3, 4, 5 };
    dynamic_array<int> vec2 = { 6, 7, 8, 9 };
    std::cout << "First vector elements and info: ";
    vec1.printElements( std::cout );
    vec1.printInfo( std::cout );

    std::cout << "Second vector elements and info: ";
    vec2.printElements( std::cout );
    vec2.printInfo( std::cout );

    std::cout << "\n\nSwap two vectors...\n\n";
    vec1.swap_with( vec2 );

    std::cout << "First vector elements and info: ";
    vec1.printElements( std::cout );
    vec1.printInfo( std::cout );
    std::cout << "Second vector elements and info: ";
    vec2.printElements( std::cout );
    vec2.printInfo( std::cout );


    std::cout << "----------------------END TEST SWAP TWO VECTORS-----------------------------\n\n";
}

void testClearAndIsEmpty()
{
    std::cout << "----------------------TEST CLEAR AND EMPTY VECTOR-----------------------------\n\n";
    dynamic_array<int> vec;
    initVector( vec );
    vec.printElements( std::cout );
    vec.printInfo( std::cout );
    
    std::cout << "Clear memory...." << std::endl;
    vec.clear();

    vec.printElements( std::cout );
    vec.printInfo( std::cout );

    if ( vec.empty() )
    {
        std::cout << "Empty vector...." << std::endl;
    }
    else
    {
        std::cout << "Still have elements in vector" << std::endl;
    }

    std::cout << "----------------------END TEST CLEAR AND EMPTY VECTOR-----------------------------\n\n";
}



int main()
{
    testConstuctorsAndOparatorEquals();
    testIterasionThoughVector();

    testIteratorInVector();
    testShrinkToFit();

    testPushBack();
    testRandomAccess();

    testInsertionInVector();
    testEraseFromVector();

    testSwapVectors();

    testClearAndIsEmpty();
}