#include <stdio.h>
#include <iostream>
#define MAXN 100
const unsigned n = 5;

unsigned a[ MAXN ];

void print()
{
	for ( unsigned i = 0; i < n; i++ )
	{
		printf( "%u ", a[ i ] + 1 );
	}
	printf( "\n" );
}

void permut( unsigned k )
{
	if ( k == 0 )
	{
		print();
	}
	else
	{
		permut( k - 1 );
		for ( unsigned i = 0; i < k - 1; i++ )
		{
			std::swap( a[ i ], a[ k - 1 ] );
			permut( k - 1 );
			std::swap( a[ i ], a[ k - 1 ] );
		}
	}
}
int main()
{
	unsigned i;
	for ( i = 0; i < n; i++ ) 
		a[ i ] = i;
	
	permut( n );
	return 0;}