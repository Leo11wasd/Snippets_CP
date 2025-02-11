ll find_set(int v, vector<ll> &parent)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}
void make_set(int v, vector<ll> &parent, vector<ll> &sizes)
{
    if (parent[v] == -1)
    {
        parent[v] = v;
        sizes[v] = 1;
    }
}

void union_sets(int a, int b, vector<ll> &parent, vector<ll> &sizes)
{
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b)
    {
        if (sizes[a] < sizes[b])
            swap(a, b);
        parent[b] = a;
        sizes[a] += sizes[b];
    }
}

