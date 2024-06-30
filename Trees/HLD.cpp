struct Node
{
    int val;
 
    Node() // The Neutral Node.. Changable!
    {
        val = -oo;
    }
 
    Node( int x )
    {
        val = x;
    }
 
    void change( int x ) // Changable!
    {
        val = x;
    }
};
 
struct SegTree
{
    int tree_size;
    vector<Node> SegData;
 
    SegTree( int n )
    {
        tree_size = 1;
        while( tree_size < n )
            tree_size *= 2;
 
        SegData.assign(2 * tree_size, Node());
    }
 
    // Note: [lx, rx] => The range of the cur Node
    //       [l, r]   => The left Node & The right Node
 
    Node merge( Node &l, Node &r )
    {
        Node ans = Node();
        ans.val = max(l.val, r.val); // Changable!
 
        return ans;
    }
 
    void init( vector<int> &arr, int nd, int lx, int rx )
    {
        if( rx - lx == 1 )
        {
            if( lx < (int)arr.size() )
                SegData[nd] = Node(arr[lx]);
            return;
        }
 
        int mid = ( lx + rx ) / 2;
        init( arr, 2 * nd + 1, lx, mid );
        init( arr, 2 * nd + 2, mid, rx );
 
        SegData[nd] = merge( SegData[2 * nd + 1], SegData[2 * nd + 2] );
    }
 
    void init( vector<int> &arr )
    {
        init( arr, 0, 0, tree_size );
    }
 
    void set( int idx, int val, int nd, int lx, int rx )
    {
        if( rx - lx == 1 )
        {
            SegData[nd].change(val);
            return;
        }
 
        int mid = ( lx + rx ) / 2;
        if( idx < mid )
            set( idx, val, 2 * nd + 1, lx, mid );
        else
            set( idx, val, 2 * nd + 2, mid, rx );
 
        SegData[nd] = merge( SegData[2 * nd + 1], SegData[2 * nd + 2] );
    }
 
    void set( int idx, int val )
    {
        set( idx, val, 0, 0, tree_size );
    }
 
    Node get( int l, int r, int nd, int lx, int rx )
    {
        if( lx >= l && rx <= r )
            return SegData[nd];
 
        if( lx >= r || rx <= l )
            return Node();
 
        int mid = ( lx + rx ) / 2;
        Node lf = get( l, r, 2 * nd + 1, lx, mid );
        Node rf = get( l, r, 2 * nd + 2, mid, rx );
 
        return merge( lf, rf );
    }
 
    int get( int l, int r )
    {
        return get( l, r, 0, 0, tree_size ).val;
    }
};
 
int isValOnEdge = 1;
vector<vector<int>> adj, edgeIdx;
vector<int>edgeTo, edgeCost;
 
int parent[N], depth[N], heavy[N], root[N], segTreePos[N];
int ans;
 
int dfs( int u )
{
    int sz = 1, maxSubtree = 0;
    for( int i = 0; i < adj[u].size(); i++ )
    {
        int v = adj[u][i], edgeIndx = edgeIdx[u][i];
        if( v != parent[u] )
        {
            edgeTo[edgeIndx] = v;
            parent[v] = u, depth[v] = depth[u] + 1;
 
            int childTreeSize = dfs(v);
            if( childTreeSize > maxSubtree )
                heavy[u] = v, maxSubtree = childTreeSize;
 
            sz += childTreeSize;
        }
    }
 
    return sz;
}
 
void build() // Don't forget to call this!
{
    memset( heavy, -1, adj.size() * sizeof(int) );
    parent[0] = -1, depth[0] = 0;
 
    dfs(0);
 
    // Connect chains to it's root & mapping chains to segment tree
    for( int chainRoot = 0, pos = 0; chainRoot < adj.size(); chainRoot++ )
    {
        if( parent[chainRoot] == -1 || heavy[parent[chainRoot]] != chainRoot )
        {
            for( int j = chainRoot; j != -1; j = heavy[j] )
                root[j] = chainRoot, segTreePos[j] = pos++;
        }
    }
}
 
// For value on Direct edge ( f, t, val ) --> call update( t, val )
void update( int treeNode, int val, SegTree &sg )
{
    sg.set( segTreePos[treeNode], val );
}
 
void queryChain( int l, int r, SegTree &sg )
{
    ans = max( ans, sg.get(l, r + 1) );
}
 
int get( int u, int v, SegTree &sg )
{
    ans = 0; // Could be changed!
    for( ; root[u] != root[v]; v = parent[root[v]] )
    {
        if( depth[root[u]] > depth[root[v]] )
            swap(u, v);
 
        queryChain( segTreePos[root[v]], segTreePos[v], sg );
    }
 
    if( depth[u] > depth[v] )
        swap(u, v);
 
    if( !isValOnEdge || u != v )
        queryChain(segTreePos[u] + isValOnEdge, segTreePos[v], sg);
 
    return ans;
}
 
void init( int &sz )
{
    adj.clear(), edgeIdx.clear(), edgeTo.clear(), edgeCost.clear();
    adj.resize(sz), edgeIdx.resize(sz), edgeTo.resize(sz), edgeCost.resize(sz);
}
 
// This is a code that deals with COST ON EDGE, when COST ON NODE simple changes must be done in the solve function
void solve()
{
    int n; cin >> n;
 
    init(n);
 
    for( int i = 0; i < n - 1; i++ )
    {
        int u, v, c; cin >> u >> v >> c;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
 
        edgeIdx[u].push_back(i), edgeIdx[v].push_back(i);
        edgeCost[i] = c;
    }
 
 
    SegTree sg = SegTree(n);
    build();
 
    for( int i = 0; i < n - 1; i++ )
        update(edgeTo[i], edgeCost[i], sg);
 
    int q; cin >> q;
    while( q-- )
    {
        int op; cin >> op;
        if( op == 1 )
        {
            int u, v; cin >> u >> v;
            cout << get(--u, --v, sg) << endl;
        }
        else
        {
            int u, c; cin >> u >> c;
            update(edgeTo[--u], c, sg);
        }
    }
}