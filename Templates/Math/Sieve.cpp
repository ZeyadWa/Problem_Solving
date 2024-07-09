*** Sieve *** O(n*log(log(n)))

const int sz = 1e5 + 7;
bool NotPrime[sz];
void Sieve()
{
    NotPrime[0] = NotPrime[1] = 1;
    for( int i = 2; i * i <= sz; i++ )
    {
        if( !NotPrime[i] )
        {
            for( int j = i * i; j < sz; j += i )
                NotPrime[j] = 1;
        }
    }
}



*** Sieve of primeFactors ***

const int N = 1e7 + 5;
int n;
vector<int>primeDivisors(N, 1);

void Sieve()
{
    vector<int>isPrime(N, 1);
    isPrime[0] = isPrime[1] = 0;
    for( int i = 2; i <= N - 4; i++ )
    {
        if( isPrime[i] )
        {
            primeDivisors[i] = i;
            for( int j = i * i; j <= N - 4; j += i )
            {
                primeDivisors[j] = i;
                isPrime[j] = 0;
            }
        }
    }
}

vector<int>ans;
while( n != 1 )
{
    int x = primeDivisors[n];
    n /= x;
    ans.push_back(x);
}


*** Linear Sieve *** O(n)

const int sz = 1e5 + 7;
bool NotPrime[sz];
vector<int>primes;
void Linear_Sieve()
{
    NotPrime[0] = NotPrime[1] = true;
    for( int i = 2; i < sz; i++ )
    {
        if( !NotPrime[i] ) 
            primes.push_back(i);
        for( int j = 0; j < primes.size() && i * primes[j] <= sz; j++ )
        {
            NotPrime[i * primes[j]] = true;
            if( i % primes[j] == 0 )
                break;
        }
    }
}

*** Sieve for large numbers "Segmented Sieve" ***

const int sz = 1e6 + 10;
bool NotPrime[sz];
int l, r;
void Segmented_Sieve()
{
    int lim = ::sqrt(r);
    for( int i = 2; i <= lim ; i++ )
    {
        for( int j = max( i * i, ( l + i - 1 ) / i * i ); j <= r; j += i )
            NotPrime[j - l] = true;
    }
    if( l == 1 )
        NotPrime[0] = true;
}
