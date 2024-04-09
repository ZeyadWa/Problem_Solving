*** Extended Euclidian ***

int Extended_Euclid(int a, int b, int& x, int& y) 
{
    if (b==0) {
        x=1;
        y=0;
        return a;
    }
    int x1,y1;
    int d = Extended_Euclid(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a/b);
    return d;
}

*** Modular Multiplicative Inverse ***

int Mod_Inverse( int A, int M )
{ 
	Extended_Euclid( int A, int M );
	return ( x % M + M ) % M;
}