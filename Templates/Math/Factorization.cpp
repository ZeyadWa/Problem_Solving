https://github.com/marioeid/Mr-Algorithms


*** factorization ***

vector<int>v;
for( int i = 1; i * i <= n ; i++ )
{
    if( n % i == 0 )
    {
        v.push_back(i);
        if( i * i != n )
               v.push_back( n / i );
    }
}


*** prime factorization ***

vector<int>v;
for( int i = 2; i * i <= n; i++ )
{
    while( n % i == 0 )
    {
        n /= i;
        v.push_back(i);
    }
}
if( n != 1 )
    v.push_back(n);