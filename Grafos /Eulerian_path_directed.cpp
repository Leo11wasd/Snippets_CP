/*
Código de ejemplo que recibe un grafo dirigido y regresa dos vectores que indican la secuencia de
nodos y aristas que se deben seguir para recorrer un camino euleriano en un grafo.

Un camino euleriano sobre un grafo es un camino que pasa por todas las aristas exactamente 1 vez

La idea del algoritmo es hacer una dfs e ir "eliminando" las aristas por las que pasamos.
Cada que nos encontramos con un nodo al que ya no le quedan aristas a la que ir, lo agregamos al inicio 
de nuestro vector respuesta.

Al inicio hay que verificar que el camino exista (todos los nodos tienen indegree==outdegree o hay exactamente
uno que tiene indegree==outdegree+1 y exactamente uno que tiene indegree+1==outdegree+1)
*/

#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef int64_t ll;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> PBDS;
ll mx = INT64_MAX;
ll mn = INT64_MIN;

void dfs(ll actual, ll aristapre, ll &sigpos, vector<ll> &nodos_res, vector<ll> &aristas_res, vector<ll> &out, vector<vector<pair<ll, ll>>> &adj, vector<ll> &siguiente)
{
    ll vecino, i;
    // for (auto &[vecino, id] : adj[actual])
    while (siguiente[actual] < adj[actual].size())
    {
        i = siguiente[actual];
        siguiente[actual]++;
        vecino = adj[actual][i].first;

        out[actual]--;
        dfs(vecino, adj[actual][i].second, sigpos, nodos_res, aristas_res, out, adj, siguiente);
    }

    nodos_res[sigpos] = actual;
    if (sigpos - 1 >= 0)
    {
        aristas_res[sigpos - 1] = aristapre;
    }

    sigpos--;
    return;
}

pair<vector<ll>, vector<ll>> eulerian(ll n, ll m, ll &sigpos, vector<vector<pair<ll, ll>>> &adj, vector<ll> &in, vector<ll> &out)
{
    vector<ll> nodos(m + 1, -1), aristas(m, -1), siguiente(n, 0);

    ll ini = -1;
    for (int i = 0; i < n; i++)
    {
        if ((in[i] + 1) == out[i])
        {
            ini = i;
        }
    }
    if (ini == -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (in[i] > 0)
            {
                ini = i;
            }
        }
    }
    dfs(ini, -1, sigpos, nodos, aristas, out, adj, siguiente);

    return {nodos, aristas};
}

//====================================================================
//                          MAIN
//====================================================================
void solved()
{
    ll n, m, u, v;
    cin >> n >> m;
    if (m == 0)
    {
        cout << "Yes\n0\n\n";
        return;
    }
    vector<vector<pair<ll, ll>>> adj(n, vector<pair<ll, ll>>());

    vector<ll> in(n, 0), out(n, 0);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        adj[u].push_back({v, i});

        out[u]++;
        in[v]++;
    }
    bool mas_in, mas_out, sepuede;
    mas_in = mas_out = 0;
    sepuede = 1;
    for (int i = 0; i < n; i++)
    {
        if (in[i] != out[i])
        {
            if (in[i] == out[i] + 1)
            {
                if (mas_in)
                {
                    sepuede = 0;
                }
                mas_in = 1;
            }
            else if (in[i] + 1 == out[i])
            {
                if (mas_out)
                {
                    sepuede = 0;
                }
                mas_out = 1;
            }
            else
            {
                sepuede = 0;
            }
        }
    }

    if (!sepuede)
    {

        cout << "No\n";
    }
    else
    {
        ll sigpos = m;
        auto [nodos, aristas] = eulerian(n, m, sigpos, adj, in, out);
        // cout << "sigpos " << sigpos << endl;
        if (sigpos != -1)
        {
            cout << "No\n";
        }
        else
        {
            cout << "Yes\n";
            for (ll x : nodos)
            {
                cout << x << " ";
            }
            cout << "\n";
            for (ll x : aristas)
            {
                cout << x << " ";
            }
            cout << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << fixed;
    // freopen("bcount.in", "r", stdin);
    // freopen("bcount.out", "w", stdout);
    ll n;
    cin >> n;
    while (n--)
        solved();
}