vector<vector<int>>adjMax;
vector<int>vis, colAssign, rowAssign;

bool canMatch( int i ) // O(E)
{
    for( int j = 0; j < adjMax[i].size(); j++ )
    {
        if( adjMax[i][j] && !vis[j] )
        {
            vis[j] = 1;
            if( colAssign[j] < 0 || canMatch(colAssign[j]) )
            {
                colAssign[j] = i, rowAssign[i] = j;
                return 1;
            }
        }
    }

    return 0;
}

vector<pair<int,int>> bipertiteMatching() // O(EV)
{
    vector<pair<int,int>> matches;

    if( adjMax.size() == 0 )
        return matches;

    int maxFlow = 0, rows = adjMax.size(), cols = adjMax[0].size();
    colAssign = vector<int>(cols, -1), rowAssign = vector<int>(cols, -1);

    for( int i = 0; i < rows; i++ )
    {
        vis = vector<int>(cols, 0);
        if( canMatch(i) )
            maxFlow++;
    }

    for( int i = 0; i < cols; i++ )
    {
        if( colAssign[i] != -1 )
            matches.push_back({colAssign[i], i});
    }

    return matches;
}