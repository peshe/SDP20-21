#include <iostream>

void factorisation( int32_t n )
{
	uint32_t i = 1;
	while ( n != 1 )
	{
		i++;
		uint32_t how = 0;
		while ( n % i == 0 )
		{
			how++;
			n /= i;
		}
		for ( uint32_t j = 0; j < how; j++ )
			std::cout << i << ' ';
	}
}

int main()
{
	std::cout << "Enter negative number, if you want to stop!" << std::endl;
	int32_t n;
	std::cin >> n;
	while ( n >= 0 )
	{
		factorisation( n );
		std::cout << std::endl;
		std::cin >> n;
	}
	
	return 0;
}