int arr[N], queryAns[N];
int n, q, sq; // sq -> sqrt(n)

struct q_data
{
    int id, block_id, l, r;

    q_data(){};
    q_data(int _l, int _r, int _id)
    {
        id = _id;
        r = _r - 1;
        l = _l - 1;
        block_id = _l / sq;
    }

    bool operator <(const q_data &A) const
    {
        if( A.block_id == block_id )
            return r < A.r;

        return block_id < A.block_id;
    }
};

vector<q_data> queries;
long long ans = 0; // Current query answer, Neutral value as initial;

void add( int idx )       // Add element in range
{

}

void remove( int idx )    // Remove element from range
{

}

void MO()   // Just change in the add & remove functions
{
    sq = sqrt(n);

    // send them 1-indexed
    for( int i = 0; i < q; ++i )
    {
        int l, r; cin >> l >> r;
        queries.push_back(q_data(l, r, i));
    }
    sort(queries.begin(), queries.end());

    int l = 1, r = 0;
    for( int i = 0; i < q; ++i )
    {
        while( queries[i].l > l ) remove(l++);
        while( queries[i].l < l ) add(--l);
        while( queries[i].r > r ) add(++r);
        while( queries[i].r < r ) remove(r--);

        queryAns[queries[i].id] = ans;
    }
}

void display()
{
    for( int i = 0; i < q; i++ )
        cout << queryAns[i] << endl;
}

/*
    Avoid TLE?
    1. Don't Define int long long ( Please don't do that )
    2. Use arrays only!
    3. Change Compiler
*/