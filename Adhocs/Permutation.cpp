int n; cin >> n;
int arr[n]
FOR(i,n){ arr[i] = i + 1; }
do{
    if( can(arr, n) ){
    FOR(i,n) cout << arr[i] << " ";
    cout << endl;
}
}while( next_permutation(arr, arr + n) );

do{

}while( next_permutation(s.begin(), s.end()));