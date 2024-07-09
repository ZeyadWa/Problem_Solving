int l = 0, r = 0, sum = 0, ans = -oo;
while( r < n )
{
    sum += v[r++];
    ans = max( ans, sum );
    while( sum <= 0 && l < r )
    {
        sum -= v[l++];
    }
}