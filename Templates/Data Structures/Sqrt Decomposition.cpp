vector<long long> arr;
vector<long long> sqrt_decomposition;

long long neutral = oo;
int sq;

long long merge(long long & val1, long long & val2)
{
    return min(val1, val2);
}

void build()
{
    int n = arr.size();
    sq = ceil(sqrt(n));

    sqrt_decomposition.assign(sq, neutral);

    for (int i = 0; i < n; ++i)
        sqrt_decomposition[i / sq] = merge(sqrt_decomposition[i / sq], arr[i]);
}

long long get(int l, int r) // 0 indexed range, O(sqrt(n))
{
    long long ans = neutral;

    while (l % sq && l <= r)
    {
        ans = merge(ans, arr[l]);
        l++;
    }

    while (l + sq - 1 <= r)
    {
        ans = merge(ans, sqrt_decomposition[l / sq]);
        l += sq;
    }

    while (l <= r)
    {
        ans = merge(ans, arr[l]);
        l++;
    }

    return ans;
}

void set(int idx, long long val) // 0 indexed
{
    arr[idx] = val;
    int l = idx - idx % sq;
    int r = l + sq - 1;
    int n = arr.size();

    long long ans = neutral;

    for( int i = l; i <= min(r, n - 1) ; ++i )
        ans = merge(ans, arr[i]);

    sqrt_decomposition[idx / sq] = ans;
}