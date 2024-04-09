bool compare( string a, string b )
{
    int len = (int)a.length();
    FOR(i, len)
    {
        if( i % 2 == 0 )
        {
            if( a[i] != b[i] )
                return a[i] < b[i];
        }
        else
        {
            if( a[i] != b[i] )
                return a[i] > b[i];
        }
    }
    return false;
}


sort(v.begin(), v.end(), compare );

