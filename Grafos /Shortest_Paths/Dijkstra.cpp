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