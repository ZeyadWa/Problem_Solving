struct Trie
{
    struct node
    {
        int nxt[26]{};
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

    void add( string& s )
    {
        int cur = 0;
        for( char i : s )
        {
            if ( trie[cur].nxt[i - 'a'] == -1 )
            {
                trie.push_back(node());
                trie[cur].nxt[i - 'a'] = (int)trie.size() -  1;
            }

            cur = trie[cur].nxt[i - 'a'];
            ++trie[cur].pref;
        }

        ++trie[cur].end;
    }

    int countPref( string& s )
    {
        int cur = 0;
        for( char i : s )
        {
            if ( trie[cur].nxt[i - 'a'] == -1 )
                return 0;

            cur = trie[cur].nxt[i - 'a'];
        }

        return trie[cur].pref;
    }

    int countEnd( string& s )
    {
        int cur = 0;
        for( char i : s )
        {
            if ( trie[cur].nxt[i - 'a'] == -1 )
                return 0;

            cur = trie[cur].nxt[i - 'a'];
        }

        return trie[cur].end;
    }
};