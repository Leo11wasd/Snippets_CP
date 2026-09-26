# Hungarian Algorithm

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
// u,v store potential
// p stores matching
// way contains information about where these minimums are reached so that we can later reconstruct the augmenting path
// A es la matriz de costos de dimensiones nxm, n<=m; A esta 1 indexada. debe tener columna y renglon 0 vacios
vector<ll> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
for (int i = 1; i <= n; ++i)
{
   p[0] = i;
   ll j0 = 0;
   vector<ll> minv(n + 1, mx);
   vector<bool> used(n + 1, false);
   do
   {
       used[j0] = true;
       ll i0 = p[j0], delta = mx, j1;
       for (int j = 1; j <= n; ++j)
           if (!used[j])
           {
               int cur = A[i0][j] - u[i0] - v[j];
               if (cur < minv[j])
                   minv[j] = cur, way[j] = j0;
               if (minv[j] < delta)
                   delta = minv[j], j1 = j;
           }
       for (int j = 0; j <= n; ++j)
           if (used[j])
               u[p[j]] += delta, v[j] -= delta;
           else
               minv[j] -= delta;
       j0 = j1;
   } while (p[j0] != 0);
   do
   {
       ll j1 = way[j0];
       p[j0] = p[j1];
       j0 = j1;
   } while (j0);
}
// To restore the answer in a more familiar form, i.e. finding for each row  
// i = 1 ... n the number ans[i] of the column selected in it, can be done as follows:
vector<int> ans(n + 1);
for (int j = 1; j <= m; ++j)
   ans[p[j]] = j;

// retreive mincost
int cost = -v[0];

```