//recuerda agregar operaciones dsu
struct Edge
{
    ll u, v, weight;
    bool operator<(Edge const &other)
    {
        return weight < other.weight;
    }
};
//esto va en el main
{
    ll n, cost;
    cost = 0;
    vector<Edge> edges, result;
    vector<ll> parents(n,-1), sizes(n);
    for (int i = 0; i < n; i++)
    {
        make_set(i, parents, sizes);
    }

    sort(edges.begin(), edges.end());

    for (Edge e : edges)
    {
        if (find_set(e.u, parents) != find_set(e.v, parents))
        {
            cost += e.weight;
            result.push_back(e);
            union_sets(e.u, e.v, parents, sizes);
        }
    }
}