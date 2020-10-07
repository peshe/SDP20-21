#include <iostream>
#include <vector>

unsigned sum( unsigned n )
{
    unsigned s = 0;
    for (unsigned i = 1; i <= n; i++ )
    {
        s += i;
    } 
    return s;
}

int sum( int a[], unsigned n )
{
    int s = 0;
    for ( unsigned i = 0; i < n; i++ )
    {
        s += a[ i ];
    }
    return s;
}

unsigned nested_sums( int a[], int b[], unsigned n, unsigned m )
{
    unsigned i, j;
    int result = 0;
    for (j = 1; j <= n; j++)
        for (i = 1; i <= m; i++)
            result += a[i] * b[j];

    return result;
}

int mult( int a[], unsigned n )
{
    int s = 1;
    for ( unsigned i = 0; i < n; i++ ) 
        s *= a[ i ];
    
    return s;
}

// Тривиалното решение е:
double power( double x, unsigned y )
{
    double res = x;
    for ( unsigned i = 1; i < y; i++ ) 
        res *= x;
    
    return res;
}
// По-късно ще разгледаме и по-хитрото и по-бъзо решение :)


//Итеративно решение
unsigned long factorial( unsigned n )
{
    unsigned long result = 1;
    for ( unsigned i = 2; i <= n; i++ ) 
        result *= i;

    return result;
}

// Рекурсивно решение
unsigned long factorial_recursive( unsigned n )
{
    if ( n == 0 || n == 1 )
    {
        return 1;
    }
    return n * factorial_recursive( n - 1 );
}

// Аналогично и за сумата на първите N числа можем да направим и рекурсивно решение
unsigned long sum_recursive( unsigned n )
{
    if ( n == 0 || n == 1 )
    {
        return n;
    }
    return n + sum_recursive( n - 1 );
}

// Проверка дали дадено число е просто
bool isPrime1( unsigned n ) /* връща true, ако е просто, и false – при съставно */
{
    if ( n == 2 )
        return true;

    unsigned i = 2;
    while ( i <= ( n/2 - 1 ) )
    {
        if ( n % i == 0 )
            return false;
        i++;
    }
    return true;
}

// Да сравним колко стъпки се правят в isPrime1 и isPrime2
bool isPrime2( unsigned n ) /* връща true, ако е просто, и false – при съставно */
{
    if ( n == 2 )
        return true;

    unsigned i = 2;
    double sq = sqrt( n );
    while ( i <= sq )
    {
        if ( n % i == 0 )
            return false;
        i++;
    }
    return true;
}


// Търсене на прости числа в интервал
// Сито на Ератостен
// Sieve of Eratosthenes
// Първо идея, после реализация

#define MAXN 30000
bool sieve[MAXN]; // допълнителна памет! не е много добре това :/
void eratosten( unsigned n )
{
    unsigned j, i = 2;
    while ( i <= n )
    {
        if ( !sieve[ i ] )
        {
            printf( "%5u", i );
            j = i * i;
            while ( j <= n )
            {
                sieve[ j ] = true;
                j += i;
            }
        }
        i++;
    }
}

//
//int main() 
//{
//
//    const unsigned n = 1200;
//    for ( unsigned i = 0; i < n; i++ ) sieve[i] = false;
//
//    eratosten( n );
//
//    return 0;
//}
//