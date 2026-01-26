ll fastpow(ll b, ll n,ll mod)
{
    ll a, c;
    a = 1;
    c = b;
    while (n > 0)
    {
        if (n&1)
        {
            a =(a*c)%mod;
        }
        n /= 2;
        c = (c*c)%mod;
        // cout<<"Pase"<<endl;
    }
    return a;
}
