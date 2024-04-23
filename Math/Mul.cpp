int mul( int a, int b )
{
    int ans = ( a * b ) % MOD;
    if( ans < 0 )
        ans += MOD;
    return ans;
}