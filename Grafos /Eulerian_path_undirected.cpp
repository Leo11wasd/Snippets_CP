/*
Código de ejemplo que recibe un grafo NO dirigido y regresa dos vectores que indican la secuencia de
nodos y aristas que se deben seguir para recorrer un camino euleriano en un grafo.

Un camino euleriano sobre un grafo es un camino que pasa por todas las aristas exactamente 1 vez

La idea del algoritmo es hacer una dfs e ir "eliminando" las aristas por las que pasamos.
Cada que nos encontramos con un nodo al que ya no le quedan aristas a la que ir, lo agregamos al inicio
de nuestro vector respuesta.

Al inicio hay que verificar que el camino exista (todos los nodos tienen grado par o hay exactamente 2 o 0
nodos con grado impar)
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

void dfs(ll actual, ll aristapre, ll &sigpos, vector<ll> &nodos_res, vector<ll> &aristas_res, vector<ll> &out, vector<vector<pair<ll, ll>>> &adj, vector<ll> &siguiente, vector<bool> &usado)
{
    ll vecino, i, arista;
    while (siguiente[actual] < adj[actual].size())
    {
        i = siguiente[actual];
        siguiente[actual]++;
        vecino = adj[actual][i].first;
        arista = adj[actual][i].second;

        if (!usado[arista])
        {
            usado[arista] = 1;
            out[actual]--;
            dfs(vecino, arista, sigpos, nodos_res, aristas_res, out, adj, siguiente, usado);
        }
    }

    nodos_res[sigpos] = actual;
    if (sigpos - 1 >= 0)
    {
        aristas_res[sigpos - 1] = aristapre;
    }

    sigpos--;
    return;
}

pair<vector<ll>, vector<ll>> eulerian(ll n, ll m, ll &sigpos, vector<vector<pair<ll, ll>>> &adj, vector<ll> &grado)
{
    //asume que ya se verificó que existe solución
    //sigpos=m
    vector<ll> nodos(m + 1, -1), aristas(m, -1), siguiente(n, 0);
    vector<bool> usado(m, 0);
    ll ini = -1;
    for (int i = 0; i < n; i++)
    {
        if ((grado[i] % 2) == 1)
        {
            ini = i;
        }
    }
    if (ini == -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (grado[i] > 0)
            {
                ini = i;
            }
        }
    }
    dfs(ini, -1, sigpos, nodos, aristas, grado, adj, siguiente, usado);

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

    vector<ll> grado(n, 0);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        grado[v]++;
        grado[u]++;
    }
    ll impares, pares;
    pares = impares = 0;
    for (int i = 0; i < n; i++)
    {
        // cout << "grado de " << i << " " << grado[i] << endl;
        if (grado[i] & 1)
        {
            impares++;
        }
        else
        {
            pares++;
        }
    }
    if (impares >= 3)
    {
        cout << "No\n";
    }
    else
    {
        ll sigpos = m;
        auto [nodos, aristas] = eulerian(n, m, sigpos, adj, grado);
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