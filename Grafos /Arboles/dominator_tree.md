# Dominator tree

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
vector<vector<int>> g, t, rg, bucket; // t = dominator tree of the nodes reachable from root
vector<int> sdom, par, idom, dsu, label, id, rev;
int T=0; //timer para registrar tin
int find_(int u, int x = 0)
{
  if (u == dsu[u])
    return x ? -1 : u;
  int v = find_(dsu[u], x + 1);
  if (v < 0)
    return u;
  if (sdom[label[dsu[u]]] < sdom[label[u]])
    label[u] = label[dsu[u]];
  dsu[u] = v;
  return x ? v : label[u];
}

void dfs(int u)
{
  T++;
  id[u] = T;
  rev[T] = u;
  label[T] = T;
  sdom[T] = T;
  dsu[T] = T;
  for (int i = 0; i < g[u].size(); i++)
  {
    int w = g[u][i];
    if (!id[w])
      dfs(w), par[id[w]] = id[u];
    rg[id[w]].push_back(id[u]);
  }
}

void build(int r, int n)
{
  dfs(r);
  n = T;
  for (int i = n; i >= 1; i--)
  {
    for (int j = 0; j < rg[i].size(); j++)
      sdom[i] = min(sdom[i], sdom[find_(rg[i][j])]);
    if (i > 1)
      bucket[sdom[i]].push_back(i);
    for (int j = 0; j < bucket[i].size(); j++)
    {
      int w = bucket[i][j];
      int v = find_(w);
      if (sdom[v] == sdom[w])
        idom[w] = sdom[w];
      else
        idom[w] = v;
    }
    if (i > 1)
      dsu[i] = par[i];
  }
  for (int i = 2; i <= n; i++)
  {
    if (idom[i] != sdom[i])
      idom[i] = idom[idom[i]];
    t[rev[i]].push_back(rev[idom[i]]);
    t[rev[idom[i]]].push_back(rev[i]);
  }
}
```
