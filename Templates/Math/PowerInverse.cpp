int power( int a, int b )
{
    if ( b <= 0 )
        return 1;

    int ret = power( mul( a, a ), b / 2 );
    if ( b % 2 )
        ret = mul( ret, a );

    return ret;
}

int inverse( int b ) { return power( b, MOD - 2 ); }