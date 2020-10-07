#include <iostream>


int main()
{
	uint32_t k;
	std::cout << "Enter positive number: ";
	std::cin >> k;

	uint64_t result = 1;

	for ( uint32_t i = 1; i <= k; ++i )
	{
		result *= i;
	}

	std::cout << "Count of digits is: " << int(log10( result )) + 1 << std::endl;
	// or
	//for (size_t digits = 0; result > 0; result /= 10, digits++);
	
	
	// but the result may quickly be overflow :/
	// we can use dark magic( math ) to resolve this problem
	// 

	return 0;
}