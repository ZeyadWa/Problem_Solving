int factorial[N];
void fact() // Don't foget to call it!
{
    factorial[0] = 1;
    for ( int i = 1; i < N; ++i )
        factorial[i] = i * factorial[i - 1] % MOD;
}