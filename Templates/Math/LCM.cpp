*** least common multiplier *** 

int LCM( int a, int b )
{
    // LCM( a, b ) == ( a * b ) / GCD( a, b )
    return a / GCD( a, b ) * b; // Avoiding Overflow!
}