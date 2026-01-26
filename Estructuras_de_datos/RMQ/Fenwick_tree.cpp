void update(vector<ll> &BIT, ll i, ll incremento, ll n)
{
    while (i <= n)
    {
        BIT[i] += incremento;
        i += (i & (-i));
    }
}

ll query(vector<ll> &BIT, ll i)
{
    ll res = 0;
    while (i > 0)
    {
        res += BIT[i];
        i -= (i & (-i));
    }
    return res;
}