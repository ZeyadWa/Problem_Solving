struct DSU
{
    int sets = 0; // How many connected components
    vector<int> Parent, Size;

    void init( int n )
    {
        Parent.resize(n + 1);
        Size.resize(n + 1);

        for ( int i = 1; i <= n; ++i )
        {
            Parent[i] = i;
            Size[i] = 1;
        }

        sets = n;
    }

    int findSet( int u )
    {
        if( Parent[u] == u )
            return u;

        return Parent[u] = findSet(Parent[u]);
    }

    bool sameSet( int u, int v )
    {
        return findSet(u) == findSet(v);
    }

    void merge( int u, int v )
    {
        int a = findSet(u);
        int b = findSet(v);

        if( a == b )
            return;

        if( Size[a] > Size[b] )
        {
            Parent[b] = a;
            Size[a] += Size[b];
        }
        else
        {
            Parent[a] = b;
            Size[b] += Size[a];
        }

        sets--;
    }
};

struct Edge
{
    int u, v, cost;
};

pair<vector<pair<int, int>>, int> MST( vector<Edge> & edges, int n ) // nodes
{
    sort(edges.begin(), edges.end(), [](Edge A, Edge B){return A.cost < B.cost;});

    DSU D;
    D.init(n);

    vector<pair<int, int>> MST_edges;
    long long MST_Cost = 0;
    for( auto & [u, v, c] : edges )
    {
        if(!D.sameSet(u, v))
        {
            D.merge(u, v);
            MST_edges.emplace_back(u, v);
            MST_Cost += c;
        }
    }

    return {MST_edges, MST_Cost};
}