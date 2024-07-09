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

    void unionSet( int u, int v )
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