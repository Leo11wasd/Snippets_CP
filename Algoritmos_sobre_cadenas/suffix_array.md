# Suffix array

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
SUFFIX ARRAY
struct SuffixArray
{
   // S puede ser un string o un vector<ll>
   string S;
   int N;
   vector<ll> sa, isa, lcp, lg;
   vector<vector<ll>> st;

   void build(string _S)
   {
       S = _S;
       N = S.size() + 1;
       genSA();
       genLCP();
       buildRMQ();
   }

   void genSA()
   {
       sa = isa = vector<ll>(N);
       sa[0] = N - 1;
       // iota(1 + all(sa), 0);
       for (int i = 1; i < sa.size(); i++)
       {
           sa[i] = i - 1;
       }
       sort(sa.begin() + 1, sa.end(), [&](ll a, ll b)
            { return S[a] < S[b]; });

       for (int i = 1; i < N; ++i)
       {
           ll a = sa[i - 1], b = sa[i];
           isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i;
       }

       for (int len = 1; len < N; len *= 2)
       {
           vector<ll> s(sa), is(isa), pos(N);
           // iota(all(pos), 0);
           for (int i = 0; i < pos.size(); i++)
           {
               pos[i] = i;
           }

           for (auto &t : s)
           {
               ll T = t - len;
               if (T >= 0)
                   sa[pos[isa[T]]++] = T;
           }

           for (int i = 1; i < N; ++i)
           {
               ll a = sa[i - 1], b = sa[i];
               isa[b] = is[a] == is[b] && is[a + len] == is[b + len] ? isa[a] : i;
           }
       }
   }

   void genLCP()
   {
       lcp = vector<ll>(N - 1);
       ll h = 0;

       for (int b = 0; b < N - 1; ++b)
       {
           ll a = sa[isa[b] - 1];
           while (a + h < S.size() && S[a + h] == S[b + h])
           {
               h++;
           }

           lcp[isa[b] - 1] = h;
           if (h)
               h--;
       }
   }

   void buildRMQ()
   {
       ll M = lcp.size();

       lg.assign(M + 1, 0);
       for (int i = 2; i <= M; i++)
           lg[i] = lg[i / 2] + 1;

       st.assign(M, vector<ll>(lg[M] + 1));

       for (int i = 0; i < M; i++)
           st[i][0] = lcp[i];

       for (int k = 1; k <= lg[M]; k++)
       {
           for (int i = 0; i + (1 << k) <= M; i++)
           {
               st[i][k] = min(
                   st[i][k - 1],
                   st[i + (1 << (k - 1))][k - 1]);
           }
       }
   }
   ll query(ll l, ll r)
   {
       ll k = lg[r - l + 1];
       return min(st[l][k], st[r - (1 << k) + 1][k]);
   }

   ll getLCP(ll i, ll j)
   {
       if (i == j)
           return S.size() - i;

       ll a = isa[i], b = isa[j];
       if (a > b)
           swap(a, b);

       return query(a, b - 1);
   }

   pair<ll, ll> find_occurrence(ll pos, ll len)
   {
       //regresa el intervalo en el SA en que el string s[pos,pos+len] es prefijo
       ll p = isa[pos];
       pair<ll, ll> ans = {p, p};

       // Find the leftmost matching suffix.
       ll l = 0, r = p - 1;

       while (l <= r)
       {
           ll mid = (l + r) / 2;

           if (query(mid, p - 1) >= len)
           {
               ans.first = mid;
               r = mid - 1;
           }
           else
           {
               l = mid + 1;
           }
       }

       // Find the rightmost matching suffix.
       l = p + 1;
       r = N - 1;

       while (l <= r)
       {
           ll mid = (l + r) / 2;

           if (query(p, mid - 1) >= len)
           {
               ans.second = mid;
               l = mid + 1;
           }
           else
           {
               r = mid - 1;
           }
       }

       return ans;
   }
};

/*
SuffixArray sa;
sa.build(v);
sa.getLCP(i,j)
*/

```