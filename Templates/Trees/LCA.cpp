// LCA -> Gets the Lowest Common Ancestor with the help of Binary Lifting Tree

int n;
vector<int>adj[N];
int parent[N], depth[N];
vector<vector<int>>jump;

void dfs( int u, int p, int dep )
{
    parent[u] = p;
    depth[u] = dep;

    for( int &v: adj[u] )
    {
        if( v != p )
            dfs(v, u, dep + 1);
    }
}

void build()
{
    dfs(1, -1, 0);
    jump = vector<vector<int>>(__lg(n) + 1, vector<int>(n + 1));

    for( int i = 1; i <= n; i++ )
        jump[0][i] = parent[i];

    for( int msk = 1; (1 << msk) <= n; msk++ )
    {
        for( int i = 1; i <= n; i++ )
        {
            if( jump[msk - 1][i] == -1 )
                jump[msk][i] = -1;
            else
                jump[msk][i] = jump[msk - 1][jump[msk - 1][i]];
        }
    }
}

int get_kth_ancestor( int u, int k )
{
    for( int i = __lg(n) + 1; i >= 0; i-- )
    {
        if( ( k >> i ) & 1 )
        {
            if( jump[i][u] == -1 )
                return -1;

            u = jump[i][u];
        }
    }

    return u;
}


int get_lca( int u, int v )
{
    if( depth[v] > depth[u] )
        swap(u, v);

    int k = depth[u] - depth[v];
    u = get_kth_ancestor(u, k);

    if( u == v )
        return u;

    for( int i = __lg(n); i >= 0; i-- )
    {
        if( jump[i][v] != jump[i][u] )
        {
            u = jump[i][u];
            v = jump[i][v];
        }
    }

    return jump[0][u];
}