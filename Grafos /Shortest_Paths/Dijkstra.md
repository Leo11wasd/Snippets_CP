# Dijkstra

## Complexity

- Time:
- Memory:

## Notes

- Inicialmente, el algoritmo toma como la distancia desde el nodo fuente hacia cualquier otro nodo d[i][j]=INF un número grande. Para los vecinos directos del nodo fuente, d[i][j] es el peso de la arista que los une.
- Utilizamos una priority queue q en la que en el tope estará el nodo que más cerca se encuentra del nodo fuente (al que menos cuesta llegar). En cada paso, tomaremos al tope de la fila e iremos a sus vecinos, actualizando su valor d[i][j] si el costo de llegar al tope de la fila desde la fuente + el costo de movernos a ese vecino del tope es menor que el costo actual d[i][j]. En caso de actualizarlo, actualizaremos su valor d[i][j] e insertaremos al nodo con su nuevo valor de distancia a la fuente. Haremos esto hasta que la fila quede vacía y verificaremos finalmente d[fuente][objetivo]. Si esta valor es INF, entonces el objetivo es inalcanzable desde la fuente.

## Code

```cpp
#define edge pair<ll, ll>

priority_queue<edge, vector<edge>, greater<edge>> q;
// <first,second> = <distancia[i],i>
edge actual;
vector<bool> visitados(n + 1, 0);
vector<ll> distancia(n + 1, mx);
distancia[1] = 0;
q.push({0, 1});
while (!q.empty())
{
    actual = q.top();
    q.pop();
    if (!visitados[actual.second])
    {
        visitados[actual.second] = 1;
        for (edge vecino : adj[actual.second])
        {
            // first de vecino es el id y second la distancia en esa arista
            if (actual.first + vecino.second < distancia[vecino.first])
            {
                distancia[vecino.first] = actual.first + vecino.second;
                q.push({distancia[vecino.first], vecino.first});
            }
        }
    }
}
```