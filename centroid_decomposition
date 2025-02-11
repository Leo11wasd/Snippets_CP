void dfs(ll v, ll padre, vector<ll> &usados, vector<vector<ll>> &adj, vector<ll> &sizes)
{
    sizes[v] = 1;
    for (ll u : adj[v])
    {
        if (u != padre && usados[u] == 0)
        {
            // ve de que tamaño es el subarbol de mis hijos, y aumenta el mio
            dfs(u, v, usados, adj, sizes);
            sizes[v] += sizes[u];
        }
    }
}

ll centroide(ll v, ll padre, vector<ll> &usados, vector<vector<ll>> &adj, vector<ll> &sizes, ll n)
{
    for (ll u : adj[v])
    {
        if (u != padre && usados[u] == 0 && 2 * sizes[u] > n)
        {
            // si existe un subtree con size mayor a n/2, entonces el centroide debe estar
            // por ahi
            return centroide(u, v, usados, adj, sizes, n);
        }
    }
    // no hubo ningun hijo con subtree mayor a n/2, entonces yo soy el centroide
    return v;
}

void resuelve(ll v, ll letra, vector<ll> &res, vector<ll> &usados, ll n, vector<vector<ll>> &adj, vector<ll> &sizes)
{

    // calculamos el tamaño de cada subarbol
    dfs(v, -1, usados, adj, sizes);
    // encontramos el centroide
    ll c = centroide(v, -1, usados, adj, sizes, sizes[v]);
    // hace lo que tenga que hacer sobre el centroide y luego resuelve para los subarboles
    for (ll u : adj[c])
    {
        if (usados[u] == 0)
        {
            resuelve(u, letra + 1, res, usados, n, adj, sizes);
        }
    }
}
