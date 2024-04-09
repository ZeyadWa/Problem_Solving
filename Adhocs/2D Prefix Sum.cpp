for(int i = 1; i <= 1000; i++)
{
    for(int j = 1; j <= 1000; j++)
    {
        pref[i][j] = pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1]+a[i][j];
    }
}

for(int i = 0; i < q; i++)
{
    long long hs, ws, hb, wb;
    cin >> hs >> ws >> hb >> wb;
    cout << pref[hb-1][wb-1]-pref[hb-1][ws]-pref[hs][wb-1]+pref[hs][ws] << endl;
}