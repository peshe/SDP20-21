#include "TemplateStack.hpp"

const size_t MAX_SIZE_BUFFER = 1024;

bool isDigit( char c )
{
	return c >= '0' && c <= '9';
}


bool isOperation( char op )
{
	return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

int applyBinaryOperation( int first, int second, char op )
{
	int result = 0;
	switch ( op )
	{
		case '+': result = first + second; break;
		case '-': result = first - second; break;
		case '*': result = first * second; break;
		case '/': result = first / second; break;
		case '^': result = (int)pow( first, second ); break;
	}
	return result;
}

int main()
{
	dsa::TemplateStack<int> numbers;
	dsa::TemplateStack<char> operations;

	char buffer[ MAX_SIZE_BUFFER ];

	std::cin.getline( buffer, MAX_SIZE_BUFFER );

	size_t i = 0;
	while ( buffer[ i ] )
	{
		if ( isDigit( buffer[ i ] ) )
		{
			numbers.push( buffer[ i ] - '0' );
		}
		else if ( isOperation( buffer[ i ] ) )
		{
			operations.push( buffer[ i ] );
			if ( numbers.size() >= 2 )
			{
				int first = numbers.top();
				numbers.pop();
				int second = numbers.top();
				numbers.pop();
				numbers.push( applyBinaryOperation( second, first, operations.top() ) );
				operations.pop();
			}
			else
			{
				std::cerr << "Not enough arguments for binary operation '" << buffer[ i ] << "'" << std::endl;
				break;
			}
		}

		++i;
	}

	if ( numbers.size() == 1 && operations.empty() )
	{
		std::cout << numbers.top() << std::endl;
	}
	else
	{
		std::cout << "Invalid expretion" << std::endl;
	}

	return 0;
}
