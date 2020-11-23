#include <iostream>
#include "ForwardList.hpp"
#include "DoubleLinkedList.hpp"

inline bool isEven( int num )
{
	return num % 2 == 0;
}

int main()
{
	std::cout << " --- Forward Lists ---\n";
	dsa::ForwardList<int> myList = { 10, 30, 20, 20, 10, 10, 10, 30, 30, 40, 20};
	std::cout << "MyList: \t";
	myList.print();
	std::cout << "Rem dup&rev:\t";
	myList.removeDuplicates().reverse().print();

	dsa::ForwardList<int> myList2 = { 10, 30, 20, 20, 40, 20, 30, 30, 10, 10, 10 };
	std::cout << "MyList2:\t";
	myList2.print();
	std::cout << "Rem rep:\t";
	myList2.removeRepeated().print(); 

	std::cout << "\n --- Doubly Linked Lists ---\n";
	dsa::DoubleLinkedList<int> myDList1 = { 5, 2, 7, 9 };
	dsa::DoubleLinkedList<int> myDList2 = { 1, 0, 3, 8, 4 };
	std::cout << "MyDList1:\t";
	myDList1.print();
	std::cout << "MyDList2:\t";
	myDList2.print();
	std::cout << "After append MyDList1:\t";
	myDList1.append( myDList2 ).print();
	std::cout << "After append MyDList2:\t";
	myDList2.print();
	std::cout << "\nAfter divide MyDList1:\t";
	myDList1.divide( isEven ).print();

	return 0;
}
