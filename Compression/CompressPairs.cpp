void Compress_pair(vector<pair<int,int>> &a, int start)
{
    int n = a.size();
    vector<pair<int, int>>pairs(2 * n);

    int j = 0, idx = 0;
    while( j < 2 * n )
    {
        pairs[j] = {a[idx].first, idx};

        j++;
        pairs[j] = {a[idx].second, idx};

        j++, idx++;
    }
    sort(pairs.begin(), pairs.end());

    int nxt = start;
    for (int i = 0; i < 2 * n; i++)
    {
        if( i > 0 && pairs[i - 1].first != pairs[i].first )
            nxt++;

        if( nxt >= a[pairs[i].second].first )
            a[pairs[i].second].second = nxt;
        else
            a[pairs[i].second].first = nxt;
    }
}