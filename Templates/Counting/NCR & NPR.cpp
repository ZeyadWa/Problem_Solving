// Define int -> Long Long!

int factorial[N];
void fact() // Don't foget to call it!
{
    factorial[0] = 1;
    for ( int i = 1; i < N; ++i )
        factorial[i] = i * factorial[i - 1] % MOD;
}

int mul( int a, int b )
{
    int ans = ( a * b ) % MOD;
    if( ans < 0 )
        ans += MOD;
    return ans;
}

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

int C( int n, int k )
{
    return factorial[n] * inverse(factorial[n - k]) % MOD * inverse(factorial[k]) % MOD;
}

int P( int n, int k )
{
    return factorial[n] * inverse(factorial[n - k]) % MOD;
}