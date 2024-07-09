struct Trie
{
    struct node
    {
        int nxt[2]{};
        int end, pref;

        node()
        {
            memset(nxt, -1, sizeof(nxt)), end = 0, pref = 0;
        }
    };

    vector<node>trie;

    Trie()
    {
        trie.push_back(node());
    }

    void add( int& X )
    {
        bitset<64>x(X);
        int cur = 0;

        for ( int i = 63; ~i; --i )
        {
            if( trie[cur].nxt[x[i]] == -1 )
            {
                trie.push_back(node());
                trie[cur].nxt[x[i]] = (int)trie.size() -  1;
            }

            cur = trie[cur].nxt[x[i]];
            ++trie[cur].pref;
        }

        ++trie[cur].end;
    }

    int solve( int& x )
    {
        bitset<64> bt(x);
        int cur = 0, ret = 0;

        for ( int i = 63, to_same, to_opposite; ~i; --i )
        {
            to_same = trie[cur].nxt[bt[i]];
            to_opposite = trie[cur].nxt[!bt[i]];

            if( to_same != -1 and trie[to_same].pref )
                cur = to_same, --trie[cur].pref;
            else
                cur = to_opposite, --trie[cur].pref, ret += ( 1 << i );
        }

        return ret;
    }

    bool search( int& X ) 
    {
        bitset<64> x(X);
        int cur = 0;
        
        for ( int i = 63; ~i; --i ) 
        {
            if (trie[cur].nxt[x[i]] == -1)
                return false;
            
            cur = trie[cur].nxt[x[i]];
        }
        
        return trie[cur].end;
    }
};