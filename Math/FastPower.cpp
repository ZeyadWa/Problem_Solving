int fastPowerMod( int base, int exponent, int modulus )
{
    int result = 1;
    base %= modulus;
    while (exponent > 0)
    {
        if ( exponent & 1 )
            result = (result * base) % modulus;

        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}