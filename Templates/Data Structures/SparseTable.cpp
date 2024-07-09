// Can't Update Range, But can answer in O(1) "In some problems"
struct SparseTable
{
    vector<vector<long long>> TableData; // Memory nlog(n)
    vector<int> LOG;

    long long neutral;

    SparseTable()
    {
        // Changable!!!
        neutral = oo;
    }

    long long merge( long long val1, long long val2 )
    {
        // Changable!!!
        return min( val1, val2 );
    }

    void build( vector<long long> &arr ) // Build time nlog(n)
    {
        int n = arr.size();
        LOG.resize(n + 1);

        for( int i = 1; i <= n; ++i )
            LOG[i] = __lg(i);

        TableData.assign(LOG[n] + 1, vector<int>(n));
        TableData[0] = arr;

        for( int i = 1; i <= LOG[n]; ++i )
        {
            int len = 1 << (i - 1);

            for( int j = 0; j + 2 * len <= n; ++j )
                TableData[i][j] = merge(TableData[i - 1][j], TableData[i - 1][j + len]);
        }
    }

    // This is the general case, but a bit slower
    long long get( int l, int r ) // 0 indexed range, O(log(N))
    {
        int len = r - l + 1, cnt = 0, ans = neutral;
        while( len )
        {
            if( len & 1 )
            {
                ans = merge(ans, TableData[cnt][l]);
                l += 1 << cnt;
            }

            len >>= 1;
            cnt++;
        }

        return ans;
    }

    // Use this for [min, max, or, and, gcd, lcm] in O(1) time
    long long fast_get(int l, int r) // 0 indexed range, fast O(1) -> but must [(x op x) = x].
    {
        int len = r - l + 1;
        int row = LOG[len];

        return merge(TableData[row][l], TableData[row][r - (1 << row) + 1]);
    }
};