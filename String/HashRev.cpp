mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

const int base1 = uniform_int_distribution<int>(30,  50)(rng), mod1 = 1000000007;
const int base2 = uniform_int_distribution<int>(51,  70)(rng), mod2 = 1000000009;

int power1[N], power2[N], inverse1[N], inverse2[N];
pair<int, int> hashing[N];
pair<int, int> hashing_rev[N];

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

void PreCalc() // Don't forget to call it before all the test cases
{
    power1[0] = power2[0] = inverse1[0] = inverse2[0] = 1;

    int pw_inv1 = power(base1, mod1 - 2, mod1);
    int pw_inv2 = power(base2, mod2 - 2, mod2);

    for( int i = 1; i < N; ++i )
    {
        power1[i] = mul(power1[i - 1], base1, mod1);
        inverse1[i] = mul(inverse1[i - 1], pw_inv1, mod1);

        power2[i] = mul(power2[i - 1], base2, mod2);
        inverse2[i] = mul(inverse2[i - 1], pw_inv2, mod2);
    }
}

void buildHash( string &s )
{
    int n = (int)s.length();
    for( int i = 0; i < n; ++i )
    {
        hashing[i].first = add(((i == 0) ? 0 : hashing[i - 1].first), mul(power1[i], s[i] - 'a' + 1, mod1), mod1);
        hashing[i].second = add(((i == 0) ? 0 : hashing[i - 1].second), mul(power2[i], s[i] - 'a' + 1, mod2), mod2);
    }

    reverse(s.begin(), s.end());

    for( int i = 0; i < n; ++i )
    {
        hashing_rev[i].first = add(((i == 0) ? 0 : hashing_rev[i - 1].first), mul(power1[i], s[i] - 'a' + 1, mod1), mod1);
        hashing_rev[i].second = add(((i == 0) ? 0 : hashing_rev[i - 1].second), mul(power2[i], s[i] - 'a' + 1, mod2), mod2);
    }
}

pair<int, int>getHash( int l, int r )
{
    pair<int, int>ans;
    ans.first = add(hashing[r].first, ((l==0)?0:-hashing[l - 1].first), mod1);
    ans.second = add(hashing[r].second, ((l==0)?0:-hashing[l - 1].second), mod2);

    ans.first = mul(ans.first, inverse1[l], mod1);
    ans.second = mul(ans.second, inverse2[l], mod2);
    return ans;
}

pair<int, int>getHash_rev(int l, int r)
{
    pair<int, int> ans;
    ans.first = add(hashing_rev[r].first, ((l==0)?0:-hashing_rev[l - 1].first), mod1);
    ans.second = add(hashing_rev[r].second, ((l==0)?0:-hashing_rev[l - 1].second), mod2);

    ans.first = mul(ans.first, inverse1[l], mod1);
    ans.second = mul(ans.second, inverse2[l], mod2);
    return ans;
}

bool is_pal( int l, int r, int n ) // send l, r( 0 indexed ) - n is the total length of the string
{
    return getHash(l, r) == getHash_rev(n - r - 1, n - l - 1);
}

pair<int, int>getFullHash( string &s )
{
    int n = (int)s.length();
    pair<int, int> hash[2];

    for( int i = 0; i < n; ++i )
    {
        hash[i&1].first = add(((i == 0) ? 0 : hash[(i - 1)&1].first), mul(power1[i], s[i] - 'a' + 1, mod1), mod1);
        hash[i&1].second = add(((i == 0) ? 0 : hash[(i - 1)&1].second), mul(power2[i], s[i] - 'a' + 1, mod2), mod2);
    }

    return hash[(n-1)&1];
}