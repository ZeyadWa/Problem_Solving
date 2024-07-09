vector<vector<ll>> dist(n + 1, vector<int>(n + 1, oo));

for(int i = 0; i < m; ++i) 
{
    ll u, v, c; cin >> u >> v >> c;
    
    dist[u][u] = 0, dist[v][v] = 0;
    dist[u][v] = min(dist[u][v], c);
    dist[v][u] = min(dist[v][u], c); // if undirected
}

for(int k = 1; k <= n; ++k)
    for(int i = 1; i <=n; ++i)
        for(int j = 1; j <= n; ++j)
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);