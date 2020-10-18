#include <iostream>

uint32_t sumDigits( int32_t n )
{
	uint32_t result = 0;

	while ( n > 0 )
	{
		result += n % 10;
		n /= 10;
	}
	return result;
}

uint32_t factorisation( int32_t n )
{
	uint32_t result = 0;
	uint32_t i = 1;
	while ( n != 1 )
	{
		i++;
		while ( n % i == 0 )
		{
			result += sumDigits( i );
			n /= i;
		}
	}
	return result;
}

bool checkSmithNumber( int32_t number )
{
	return factorisation( number ) == sumDigits( number );
}

int main()
{
	std::cout << "Enter negative number, if you want to stop!" << std::endl;
	int32_t n;
	std::cin >> n;
	while ( n >= 0 )
	{
		if ( checkSmithNumber( n ) )
		{
			std::cout <<  n << " is a Smith number" << std::endl;
		}
		else
		{
			std::cout <<  n << " is not Smith number" << std::endl;
		}
		std::cout << std::endl;
		std::cin >> n;
	}
	
	/*
	uint32_t countSmithNumbers = 0;
	for ( uint32_t i = 1; i < 10000; ++i )
	{
		if ( checkSmithNumber( i ) )
		{
			countSmithNumbers++;
		}
		double percentage = ( (double)(countSmithNumbers) / i ) * 100;
		std::cout << "Smith numbers in first " << i << " numbers are " << percentage << "%" << std::endl;
	}
	*/
	return 0;
}