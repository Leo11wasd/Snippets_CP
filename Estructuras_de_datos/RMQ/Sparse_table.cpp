vector<vector<ll>> build(vector<ll> &v)
{
    // arreglo a 1 indexado
    ll a, b, n, ln;
    n = v.size();
    ln = log2(n);
    vector<vector<ll>> rmq(n + 1, vector<ll>(ln + 1));
    for (int i = 1; i <= n; i++)
    {
        rmq[i][0] = v[i];
    }
    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
        {
            a = rmq[i][j - 1];
            b = rmq[i + (1 << (j - 1))][j - 1];
            rmq[i][j] = min(a, b);
        }
    }
    return rmq;
}

ll query(vector<vector<ll>> &rmq, ll i, ll j)
{
    if (i > j)
    {
        return 0;
    }
    ll l = log2(j - i + 1);
    // para operaciones idempotentes f(f(x))=f(x)
    // si no es idempotente, ir brincando de potencia de dos en potencia
    // de dos hasta cubrir el intervalo

    return min(rmq[i][l], rmq[j - (1 << l) + 1][l]);
}