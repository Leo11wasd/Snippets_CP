
# Small to large merging / DSU on trees

## Complexity

- Time: $O(nlogn)$
- Memory: $O(nlogn)$

## Notes

- para responder preguntas del tipo: cada nodo tiene alguna característica. Para cada nodo, dime algo sobre las características de los nodos en su subárbol.
- Ejemplo: cada nodo tiene un color. para cada nodo, determina cuáles colores son los que aparecen con mayor frecuencia en su subárbol (pueden ser varios si empatan en cantidad de apariciones en él subárbol) e imprime su suma.


## Code

```cpp
vector<vector<ll>> adj, vec;
vector<ll> cnt, sz, colores, res;
ll suma, maximo;

void dfs_sz(ll cur, ll pre)
{
   sz[cur]++;
   for (ll vecino : adj[cur])
   {
       if (vecino != pre)
       {
           dfs_sz(vecino, cur);
           sz[cur] += sz[vecino];
       }
   }
}

void actualiza(ll cur)
{
   cnt[colores[cur]]++;
   if (cnt[colores[cur]] == maximo)
   {
       suma += colores[cur];
   }
   else if (cnt[colores[cur]] > maximo)
   {
       suma = colores[cur];
       maximo = cnt[colores[cur]];
   }
}

void dfs_dsu(ll cur, ll pre, bool keep)
{
   ll heavy = -1;
   ll pesoh = 0;
   // encuentra al hijo heavy
   for (ll vecino : adj[cur])
   {
       if (vecino != pre)
       {
           if (sz[vecino] > pesoh)
           {
               pesoh = sz[vecino];
               heavy = vecino;
           }
       }
   }
   // resuelve para los light
   for (ll vecino : adj[cur])
   {
       if (vecino != pre && vecino != heavy)
       {
           dfs_dsu(vecino, cur, 0);
       }
   }

   // resuelve para el heavy
   // y jalate lo del heavy

   if (heavy != -1)
   {
       dfs_dsu(heavy, cur, 1);
       swap(vec[heavy], vec[cur]);
   }

   // resuelve aqui, agregando lo de los light
   vec[cur].push_back(cur);
   //incrementamos cnt[color[cur]] y vemos si modifica la respuesta
   actualiza(cur);

   for (ll vecino : adj[cur])
   {
       if (vecino != pre && vecino != heavy)
       {
           for (ll x : vec[vecino])
           {
               vec[cur].push_back(x);
               actualiza(x);
           }
       }
   }

   res[cur] = suma;
   // limpia si keep=0
   if (keep == 0)
   {
       for (ll x : vec[cur])
       {
           cnt[colores[x]]--;
       }
       suma = maximo = 0;
   }
}
// uso
dfs_sz(0, 0);
suma = maximo = 0;
dfs_dsu(0, 0, 0);
```