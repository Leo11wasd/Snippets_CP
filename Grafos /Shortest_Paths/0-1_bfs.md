# 0-1 BFS

## Complexity

- Time:
- Memory:

## Notes

- Si queremos calcular shortest paths al modo de Dijkstra, pero sabemos que los pesos del grafo son solamente 0 o 1, podemos
utilizar dos filas en lugar de una priority queue. Agregamos a una u otra dependiendo si llegamos a ese nodo a traves de una arista de peso 0 o no.
- Utilizar este enfoque reduce la complejidad del algoritmo.

## Code

```cpp
vector<int> d(n, INF);
d[s] = 0;
queue<int> q0, q1;
q0.push(s);
while (!q0.empty())
{
    int v = q0.front();
    q0.pop();
    for (auto edge : adj[v])
    {
        int u = edge.first;
        int w = edge.second;
        if (d[v] + w < d[u])
        {
            d[u] = d[v] + w;
            if (w == 0)
                q0.push(u);
            else
                q1.push(u);
        }
    }
    if (q0.empty())
        swap(q0, q1);
}
```