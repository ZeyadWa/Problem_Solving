mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

const int base1 = uniform_int_distribution<int>(30,  50)(rng), mod1 = 1000000007;
const int base2 = uniform_int_distribution<int>(51,  70)(rng), mod2 = 1000000009;

pair<int,int> perm[N];
pair<int, int> hashing[N];

int add( int a, int b, int mod )
{
    int ans = a + b;
    if( ans >= mod )
        ans -= mod;
    if( ans < 0 )
        ans += mod;
    return ans;
}

int mul( int a, int b, int mod )
{
    int ans = ( a * b ) % mod;
    if( ans < 0 )
        ans += mod;
    return ans;
}

int power( int a, int b, int mod )
{
    if ( b <= 0 )
        return 1;
    int ret = power( mul( a, a, mod ), b / 2, mod );
    if ( b % 2 )
        ret = mul( ret, a, mod );
    return ret;
}

void buildHash( vector<int> &v )
{
    int n = (int)v.size();
    for( int i = 0; i < n; ++i )
    {
        hashing[i].first = add(((i == 0)? 0 : hashing[i - 1].first), power(v[i], base1, mod1), mod1);
        hashing[i].second = add(((i == 0)? 0 : hashing[i - 1].second), power(v[i], base2, mod2), mod2);
    }

    for( int i = 1; i <= n; i++ )
    {
        perm[i].first = power( i, base1, mod1 );
        perm[i].second = power( i, base2, mod2 );

        if(i)
        {
            perm[i].first = add( perm[i].first, perm[i - 1].first, mod1 );
            perm[i].second = add( perm[i].second, perm[i - 1].second, mod2 );
        }
    }
}

pair<int, int>getHash( int l, int r )
{
    pair<int, int>ans;

    ans.first = add(hashing[r].first, ((l==0)?0:-hashing[l - 1].first), mod1);
    ans.second = add(hashing[r].second, ((l==0)?0:-hashing[l - 1].second), mod2);

    return ans;
}