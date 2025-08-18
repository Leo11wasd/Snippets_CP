    ll ini = 0, fin = 2e3;
    ll med,ans;

    bool sepuede;
    while (ini <= fin)
    {
        med = ini + ((fin - ini) / 2);
        sepuede=func();
        // cout<<med<<'\n';
        if (sepuede)
        {
            ans = med;
            fin = med - 1;
        }
        else
        {
            ini = med + 1;
        }
    }
    return ans;