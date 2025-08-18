bool miller_rabin(ll n)
{
    // n es primo? Preciso antes del número 3825123056546413051. Si se quiere extender hay q usar más primos 
    //en la muestra : https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test "Testing against small sets of bases"
    // for 2^64, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.

    if (n == 2)
    {
        return true;
    }
    if (n == 1 || !(n & 1))
    {
        return false;
    }
    ll d = n - 1, s = 0;
    // n-1 =d*2^s
    while (d % 2 == 0)
    {
        s++;
        d /= 2;
    }
    // primos elegidos "al azar"
    vector<ll> a({2, 3, 5, 7, 11, 13, 17, 19, 23});
    for (ll ai : a)
    {
        if (ai <= n - 2)
        {
            ll ad = fastpow(ai, d, n);
            bool prime = false;
            if (ad % n != 1)
            {
                for (ll r = 0; r < s; r++)
                {
                    ll rr = fastpow(2, r, n);
                    ll ard = fastpow(ad, rr, n);
                    if (ard % n == n - 1)
                    {
                        prime = true;
                    }
                }
            }
            else
            {
                prime = true;
            }
            if (!prime)
            {
                return false;
            }
        }
    }
    return true;
}