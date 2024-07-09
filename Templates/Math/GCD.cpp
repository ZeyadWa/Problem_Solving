*** greatest common divisor ***

int GCD( int a, int b )
{
    // GCD( a, b ) == GCD( b, a % b )
    // stopping condition if ( b == 0 )
    // Time complexity O( log( max( a, b )) )
    while( b != 0 )
    {
        int A = a;
        a = b;
        b = A % b;
    }
    return a;
}
