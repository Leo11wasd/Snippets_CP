/*
   Given a list of n integers, your task is to calculate for each element x:
   a) the number of elements y such that x | y = x (submascaras de x)
   b) the number of elements y such that x & y = x (supermascaras de x)
   c) the number of elements y such that x & y != 0
   dónde | y & son operadores bitwise
   */
   ll n, val;
   cin >> n;
   vector<ll> a(3e6 + 2, 0), b(3e6 + 2, 0), v(n);
   for (int i = 0; i < n; i++)
   {
       cin >> val;
       a[val]++;
       b[val]++;
       v[i] = val;
   }
   for (int i = 0; i < 20; ++i)
   {
       for (int mask = 0; mask < (1 << 20); ++mask)
       {
           if ((mask & (1 << i)))
               a[mask] += a[mask ^ (1 << i)];
       }
   }
   for (int i = 0; i < 20; ++i)
   {
       for (int mask = 0; mask < (1 << 20); ++mask)
       {
           if ((mask & (1 << i)) == 0)
               b[mask] += b[mask | (1 << i)];
       }
   }
   for (int i = 0; i < n; i++)
   {
       // a[v[i]]      b[v[i]]     c[v[i]]
       cout << a[v[i]] << " " << b[v[i]] << " " << n - a[((1 << 20) - 1) ^ v[i]] << "\n";
   }
