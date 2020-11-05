#include "TemplateQueue.hpp"

template < typename T>
bool isSorted( dsa::TemplateQueue<T>&& Q )
{
	bool success = true;

	T temp = Q.front();
	size_t countEl = Q.size();

	Q.pop();
	bool asc = temp <= Q.front();
	for ( size_t i = 0; i < countEl - 1; ++i )
	{
		if ( asc && temp <= Q.front() )
		{
			Q.push( temp );
			temp = Q.front();
			Q.pop();
		}
		else if ( !asc && temp >= Q.front() )
		{
			Q.push( temp );
			temp = Q.front();
			Q.pop();
		}
		else
		{
			Q.push( temp );
			for ( size_t j = i; j < countEl - 1; ++j )
			{
				Q.push( Q.front() );
				Q.pop();
			}
			success = false;
			break;
		}
	}
	return success;
}


int main()
{

	dsa::TemplateQueue<int> Q;
	for ( int i = 1; i <= 10; ++i )
	{
		Q.push( -i );
	}
	//Q.push( 10 ); add for unsorted queue

	Q.print();

	std::cout << ( isSorted( std::move(Q) ) ? "Yey" : "Ney" ) << std::endl; ;
	Q.print();

	return 0;
}