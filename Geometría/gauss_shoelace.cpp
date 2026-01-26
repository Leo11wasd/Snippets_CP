    ll n, x, y;
    cin >> n;
    vector<pair<ll, ll>> v;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        v.push_back({x, y});
    }
    double res = 0;
    for (int i = 0; i < n; i++)
    {
        res += v[i].first * v[(i + 1) % n].second;
        res -= v[i].second * v[(i + 1) % n].first;
    }
    res /= 2;
    cout << abs(res) << endl;