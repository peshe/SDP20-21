#include <stdio.h>   // printf(), putchar()
#include <stdbool.h> // bool type


/** definitions for used and unused numbers */
#define USED true
#define UNUSED false


/// the power of the set to permute
#define MAXN 4

/// the set we are permuting
int given[ MAXN ] = { 3, 11, 23, 7 };

/// buffer for generating the current permutation
int cur_perm[ MAXN ];

/// markers for used in current permutation
bool used[ MAXN ] = { UNUSED, };

/// outputs the current permutation
void print_perm()
{
	for ( int i = 0; i < MAXN; i++ )
		printf( "%d ", cur_perm[ i ] );

	putchar( '\n' );
}

void perm( int i )
{

	if ( i >= MAXN )
	{
		// the bottom of the recursion,
		// when the last element is placed
		print_perm();
		return;
	}

	for ( int k = 0; k < MAXN; k++ )
	{
		// trying to use the k-th element of the set
		if ( used[ k ] == UNUSED )
		{
			used[ k ] = USED;          // marking it as used 
			cur_perm[ i ] = given[ k ];  // saving it's value
			perm( i + 1 );             // generating the n-1 permutation
			used[ k ] = UNUSED;        // unmarking after coming back form the recursion call
		}
	}
}

int main()
{
	/* run the algorithm stating from the element on index 0*/
	perm( 0 );

	return 0;
}