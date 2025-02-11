vector<ll> indegree(V, 0);
for (int i = 0; i < V; i++)
{
    for (auto it : adj[i])
    {
        indegree[it]++;
    }
}
queue<ll> q;
for (int i = 0; i < V; i++)
{
    if (indegree[i] == 0)
    {
        q.push(i);
    }
}
vector<ll> topo;
while (!q.empty())
{
    ll node = q.front();
    q.pop();
    topo.push_back(node);
    // remove his childs
    for (auto it : adj[node])
    {
        indegree[it]--;
        if (indegree[it] == 0)
        {
            q.push(it);
        }
    }
}
