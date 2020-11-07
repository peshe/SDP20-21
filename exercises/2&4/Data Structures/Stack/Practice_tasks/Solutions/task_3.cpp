#include <iostream>
#include <string>
#include "TemplateStack.hpp"

inline bool isDigit( char c )
{
	return c >= '0' && c <= '9';
}

inline bool isOperation( char op )
{
	return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

double applyBinaryOperation( double first, double second, char op )
{
	double result = 0;
	switch ( op )
	{
		case '+': result = first + second; break;
		case '-': result = first - second; break;
		case '*': result = first * second; break;
		case '/': result = first / second; break;
		case '^': result = pow( first, second ); break;
	}
	return result;
}

int main()
{
	dsa::TemplateStack<double> calc;

	std::string input;
	std::getline( std::cin, input );

	for ( char currChar : input )
	{
		if ( isDigit( currChar ) )
		{
			calc.push( currChar - '0' );
		}
		else if ( isOperation( currChar ) )
		{
			if ( calc.size() >= 2 )
			{
				double other = calc.top();
				calc.pop();
				double& top = calc.top();
				top = applyBinaryOperation( top, other, currChar );
			}
			else
			{
				std::cerr << "Not enough arguments for binary operation '" << currChar << "'" << std::endl;
				break;
			}
		}
	}

	if ( calc.size() == 1 )
	{
		std::cout << calc.top() << std::endl;
	}
	else
	{
		std::cout << "Invalid expression" << std::endl;
	}

	return 0;
}
