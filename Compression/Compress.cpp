void Compress(vector<int> &a, int start) 
{
    int n = a.size();
    vector<pair<int, int>>pairs(n);
    
    for( int i = 0; i < n; ++i ) 
        pairs[i] = {a[i], i};
    sort(pairs.begin(), pairs.end());
    
    int nxt = start;
    for (int i = 0; i < n; i++) 
    {
        if( i > 0 && pairs[i - 1].first != pairs[i].first ) 
            nxt++;
        a[pairs[i].second] = nxt;
    }
}