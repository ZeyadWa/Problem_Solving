struct Point 
{
    int x, y; // Could be double or integer

    bool operator == ( Point const& t ) const
    {
        return x == t.x && y == t.y;
    }
};

int orientation( Point a, Point b, Point c )
{
    double v = a.x * ( b.y - c.y ) + b.x * ( c.y - a.y ) + c.x * ( a.y - b.y );

    if( v < 0 ) return -1; // clockwise
    if( v > 0 ) return +1; // counter-clockwise

    return 0;
}

bool cw( Point a, Point b, Point c, bool include_collinear )
{
    int o = orientation(a, b, c);
    return o < 0 || ( include_collinear && !o );
}

bool collinear( Point a, Point b, Point c ){ return orientation( a, b, c ) == 0; }

vector<Point> convexHull( vector<Point>& a, bool include_collinear = false ) // Nlog(N)
{
    Point p0 = *min_element(a.begin(), a.end(), [](Point a, Point b)
    {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });

    sort(a.begin(), a.end(), [&p0](const Point& a, const Point& b)
    {
        int o = orientation(p0, a, b);
        if ( !o )
            return ( p0.x - a.x ) * ( p0.x - a.x ) + ( p0.y - a.y ) * ( p0.y - a.y ) < ( p0.x - b.x ) * ( p0.x - b.x ) + ( p0.y - b.y ) * ( p0.y - b.y );

        return o < 0;
    });

    if( include_collinear )
    {
        int i = (int)a.size() - 1;

        while( i >= 0 && collinear(p0, a[i], a.back()) )
            i--;

        reverse(a.begin()+i+1, a.end());
    }

    vector<Point> ans;
    for( int i = 0; i < (int)a.size(); i++ )
    {
        while( ans.size() > 1 && !cw(ans[ans.size()-2], ans.back(), a[i], include_collinear) )
            ans.pop_back();

        ans.push_back(a[i]);
    }

    if ( !include_collinear && ans.size() == 2 && ans[0] == ans[1])
        ans.pop_back();

    return ans;
}