const int N = 2e5 + 5, oo = 1e9;
vector<int> adj[N];
int dist[N];
int parent[N];
int n, m;
void bfs(int src)
{
    for (int i = 1; i <= n; ++i) dist[i] = oo;
    dist[src] = 0;
    parent[src] = src;

    queue<int> q;
    q.push(src);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for( int i : adj[u] )
        {
            if( dist[i] == oo )
            {
                dist[i] = dist[u] + 1;
                parent[i] = u;
                q.push(i);
            }
        }
    }
}
