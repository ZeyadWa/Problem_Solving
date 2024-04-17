vector<vector<int>> unity;

vector<vector<int>> mul( vector<vector<int>> mat1, vector<vector<int>> mat2 )
{
    int n = (int)mat1.size();
    vector<vector<int>>ans(n, vector<int>(n));

    for( int i = 0; i < n; i++ )
    {
        for( int j = 0; j < n; j++ )
        {
            for( int k = 0; k < n; k++ )
            {
                ans[i][j] += ( mat1[i][k] * mat2[k][j] ) % MOD;
                if( ans[i][j] >= MOD ) ans[i][j] -= MOD;
            }
        }
    }

    return ans;
}

vector<vector<int>> fast_power( vector<vector<int>> mat, int n )
{
    if( n <= 0 ) return unity; // Change this to N*N Unity matrix

    vector<vector<int>> ret = fast_power( mul( mat, mat ), n / 2 );
    if( n & 1 ) ret = mul( ret, mat );

    return ret;
}

void initUnity( int x )
{
    unity.assign(x, vector<int>(x));
    for( int i = 0; i < x; ++i )
        unity[i][i] = 1;
}