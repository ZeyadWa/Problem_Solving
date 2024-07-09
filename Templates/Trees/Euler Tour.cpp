vector<vector<int>>adj;
vector<int>in, out, val;
int timer;

void tour( int u, int p = -1 )
{
    in[u] = timer++;
    for( int i : adj[u] )
        if( i != p )
            tour(i, u);

    out[u] = timer++;
}

// Don't forget to call the function & resize the vectors!