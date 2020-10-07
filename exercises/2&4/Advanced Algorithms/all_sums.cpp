#include <stdio.h> // printf

/// maximum number of addends
#define MAXN 100

/// all addends -> addends[i] contains the "i" summand
int addends[MAXN];

/// simple result output
void print_sum( unsigned int len )
{

	for ( unsigned int i = 1; i < len; i++ )
		printf( "%d + ", addends[ i ] );

	printf( "%d\n", addends[ len ] );
}

void create_next_sum( unsigned int n, int pos )
{

	if ( n == 0 )
	{
		// bottom case
		print_sum( pos - 1 );
		return;
	}

	for ( unsigned int k = n; k >= 1; k-- )
	{
		// get a smaller number
		addends[ pos ] = k;
		// represent the smaller number as sum, too.
		if ( addends[ pos ] <= addends[ pos - 1 ] )
			create_next_sum( n - k, pos + 1 );
	}
}

int main()
{

	/* number to be split */
	unsigned int n = 4;

	/* initialize step */
	addends[ 0 ] = n + 1;

	/* run the algorithm */
	create_next_sum( n, 1 );

	return 0;
}