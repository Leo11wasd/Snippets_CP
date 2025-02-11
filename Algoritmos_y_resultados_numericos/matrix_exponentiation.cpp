ll k;
ll MOD = 1e9 + 7;
vector<vector<ll>> multimat(vector<vector<ll>> A, vector<vector<ll>> B)
{
    vector<vector<ll>> C(k + 1, vector<ll>(k + 1));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int x = 0; x < k; x++)
            {
                C[i][j] = (C[i][j] + (A[i][x] * B[x][j]) % MOD) % MOD;
            }
        }
    }
    return C;
}
vector<vector<ll>> matpow(vector<vector<ll>> A, ll p)
{
    if (p == 1)
    {
        return A;
    }
    if (p & 1)
    {
        return multimat(A, matpow(A, p - 1));
    }
    vector<vector<ll>> X = matpow(A, p / 2);
    return multimat(X, X);
}