const int N = 1e5 + 5;

struct node
{
    int index, cost;
};

struct cmp
{
    bool operator()( node &a, node &b )
    {
        return a.cost > b.cost;
    }
};
vector<vector<node>>adj(N);
vector<int>dist(N, oo), vis(N, 0);

int dijkstra( int u, int en )
{
    priority_queue<node, vector<node>, cmp>pq;
    pq.push({u, 0});
    dist[u] = 0;

    while( !pq.empty() )
    {
        auto top = pq.top();
        pq.pop();

        if( vis[top.index] )
            continue;
        vis[top.index] = 1;

        for( auto i : adj[top.index] )
        {
            if( dist[i.index] > i.cost + top.cost )
            {
                dist[i.index] = i.cost + top.cost;
                pq.push({i.index, i.cost + top.cost});
            }
        }
    }

    return dist[en];
}

void clear( int n )
{
    for( int i = 0; i <= n; i++ )
        adj[i].clear(), dist[i] = oo, vis[i] = 0;
}

void solve()
{
    int n, m; cin >> n >> m;
    clear(n);

    for( int i = 0; i < m; ++i )
    {
        int u, v, cost; cin >> u >> v >> cost;
        adj[u].push_back({v, cost});
    }

    int st, en; cin >> st >> en;

    int ans = dijkstra(st, en);
    if( ans == oo )
        no;
    else
        cout << ans;
}
