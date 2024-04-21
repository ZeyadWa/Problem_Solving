struct Node
{
    int val;

    Node() // The Neutral Node.. Changable!
    {
        val = 0;
    }

    Node( int x )
    {
        val = x;
    }

    void change( int x ) // Changable!
    {
        val = x;
    }
};

struct SegTree
{
    int tree_size;
    vector<Node> SegData;

    SegTree( int n )
    {
        tree_size = 1;
        while( tree_size < n )
            tree_size *= 2;

        SegData.assign(2 * tree_size, Node());
    }

    // Note: [lx, rx] => The range of the cur Node
    //       [l, r]   => The left Node & The right Node

    Node merge( Node &l, Node &r )
    {
        Node ans = Node();
        ans.val = l.val + r.val; // Changable!

        return ans;
    }

    void init( vector<int> &arr, int nd, int lx, int rx )
    {
        if( rx - lx == 1 )
        {
            if( lx < (int)arr.size() )
                SegData[nd] = Node(arr[lx]);
            return;
        }

        int mid = ( lx + rx ) / 2;
        init( arr, 2 * nd + 1, lx, mid );
        init( arr, 2 * nd + 2, mid, rx );

        SegData[nd] = merge( SegData[2 * nd + 1], SegData[2 * nd + 2] );
    }

    void init( vector<int> &arr )
    {
        init( arr, 0, 0, tree_size );
    }

    void set( int idx, int val, int nd, int lx, int rx )
    {
        if( rx - lx == 1 )
        {
            SegData[nd].change(val);
            return;
        }

        int mid = ( lx + rx ) / 2;
        if( idx < mid )
            set( idx, val, 2 * nd + 1, lx, mid );
        else
            set( idx, val, 2 * nd + 2, mid, rx );

        SegData[nd] = merge( SegData[2 * nd + 1], SegData[2 * nd + 2] );
    }

    void set( int idx, int val )
    {
        set( idx, val, 0, 0, tree_size );
    }

    Node get( int l, int r, int nd, int lx, int rx )
    {
        if( lx >= l && rx <= r )
            return SegData[nd];

        if( lx >= r || rx <= l )
            return Node();

        int mid = ( lx + rx ) / 2;
        Node lf = get( l, r, 2 * nd + 1, lx, mid );
        Node rf = get( l, r, 2 * nd + 2, mid, rx );

        return merge( lf, rf );
    }

    int get( int l, int r )
    {
        return get( l, r, 0, 0, tree_size ).val;
    }
};