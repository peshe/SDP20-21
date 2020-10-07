#include <stdio.h> // printf()

#define N 5
#define K 2

/// an array to hold the last line from the triangle
int line[ N + 1 ];

int calc_n_over_k()
{
	// first element of the line is  always 1 ... 
	line[ 0 ] = 1;
	// generate lines
	for ( int i = 1; i <= N; i++ )
	{
		// generate lines members
		line[ i ] = 1; //... last also

		for ( int j = i - 1; j > 0; j-- )
		{
			// every other element is a sum 
			// of the two numbers from the previous line 
			line[ j ] += line[ j - 1 ];
		}
	}

	// the result is the k-th element in the n -th line 
	return line[ K ];
}

int main()
{

	printf( "( %d )\n", N );
	printf( "(   ) = %d\n", calc_n_over_k() );
	printf( "( %d )\n", K );

	return 0;
}