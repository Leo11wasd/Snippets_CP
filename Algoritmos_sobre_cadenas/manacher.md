# Manacher's Algorithm

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
vector<ll> manacher_odd(string s)
{
   ll n = s.size();
   s = "$" + s + "^";
   vector<ll> p(n + 2);
   ll l = 0, r = 1;
   for (int i = 1; i <= n; i++)
   {
       if (i <= r)
       {
           p[i] = min(r - i, p[l + (r - i)]);
       }
       while (s[i - p[i]] == s[i + p[i]])
       {
           p[i]++;
       }
       if (i + p[i] > r)
       {
           l = i - p[i], r = i + p[i];
       }
   }
   return vector<ll>(begin(p) + 1, end(p) - 1);
}
vector<ll> manacher(string s)
{
   string t;
   for (auto c : s)
   {
       t += string("#") + c;
   }
   auto res = manacher_odd(t + "#");
   return vector<ll>(begin(res) + 1, end(res) - 1);
}
```