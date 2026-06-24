# Virtual tree

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
const ll MAXN = 2e5 + 10;
const ll LOGN = 20;

vector<pair<ll, ll>> adj[MAXN];  // Adjacency list of the original graph
vector<ll> ver[MAXN]; // For color c, ver[c] stores vertices with color c
vector<ll> aux_g[MAXN];           // Adjacency list for the virtual tree
ll color[MAXN];                  // Color/feature of each vertex
ll tmr, n;                 // Global time counter and number of vertices
ll up[LOGN][MAXN], dep[MAXN], tin[MAXN]; // For computing LCA and entry time

// DP arrays for dynamic programming on the virtual tree
ll dp[MAXN], sum[MAXN];

// Preprocessing function: DFS to compute tin, up array, and dep
void dfs_precalc(ll v, ll p)
{
   tin[v] = ++tmr;
   up[0][v] = p;
   dep[v] = dep[p] + 1;
   for (ll i = 1; i < LOGN; ++i)
       up[i][v] = up[i - 1][up[i - 1][v]];
   for (auto [to, id_edge] : adj[v])
       if (to != p)
           dfs_precalc(to, v);
}

// Function to compute LCA using binary lifting
ll getlca(ll x, ll y)
{
   if (dep[x] < dep[y])
       swap(x, y);
   for (int i = LOGN - 1; i >= 0; --i)
       if (dep[up[i][x]] >= dep[y])
           x = up[i][x];
   if (x == y)
       return x;
   for (int i = LOGN - 1; i >= 0; --i)
       if (up[i][x] != up[i][y])
       {
           x = up[i][x];
           y = up[i][y];
       }
   return up[0][x];
}
// una dfs final que agrupa los resultados calculados por color
// no siempre es necesario implementar esta función
void dfs_resolve(ll cur, ll pre, vector<ll> &ans)
{}

// DFS on the virtual tree to perform DP.
// Parameter c — target color for which counting is performed.
// su implementación depende del problema.
void dfs_calc(ll cur, ll pre, ll c)
{}

// Function to build a virtual tree for color c and perform DP.
void calc_aux(ll c)
{
   // cout << "resolvemos color " << c << endl;
   auto p = ver[c];
   if (p.empty())
       return;
   // Sort vertices by entry time (tin) — DFS traversal order.
   sort(p.begin(), p.end(), [&](const ll a, const ll b)
        { return tin[a] < tin[b]; });
   vector<ll> verstk = {0}; // Initialize stack with the root of tree T (vertex 0).
   aux_g[0].clear();
   auto add = [&](ll u, ll v)
   {
       aux_g[u].push_back(v);
       aux_g[v].push_back(u);
   };
   // Process each vertex from set p, maintaining a stack to build the virtual tree.
   for (auto u : p)
   {
       if (u == 0)
           continue;
       ll lca = getlca(u, verstk.back());
       if (lca != verstk.back())
       {
           while (verstk.size() >= 2 && tin[lca] < tin[verstk[verstk.size() - 2]])
           {
               add(verstk.back(), verstk[verstk.size() - 2]);
               verstk.pop_back();
           }
           if (verstk.size() >= 2 && tin[lca] != tin[verstk[verstk.size() - 2]])
           {
               aux_g[lca].clear();
               add(verstk.back(), lca);
               verstk.back() = lca;
           }
           else
           {
               add(verstk.back(), lca);
               verstk.pop_back();
           }
       }
       aux_g[u].clear();
       verstk.push_back(u);
   }
   while (verstk.size() > 1)
   {
       add(verstk.back(), verstk[verstk.size() - 2]);
       verstk.pop_back();
   }
   // Perform DP on the virtual tree, starting from root 0.
   return dfs_calc(0, -1, c);
}

/*
   1. recibe los colores/features de los nodos y realiza ver[color[i]].push_back(i)
   1. recibe el grafo de input
   2. dfs_precalc(0, 0);
   3. Para cada color c , calc_aux(c)
   4. Si hay que juntar información de las llamadas por color, realiza una dfs final
*/
```