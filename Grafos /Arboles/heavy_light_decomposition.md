# Heavy-light decomposition

## Complexity

- Time:
- Memory:

## Notes

// ejemplo de uso

LazySeg seg(n);

// false = valores en vertices; true = valores en aristas.

HLD<false> hld(n, seg);

hld.addEdge(0, 1);

// En ese caso valores[i] = peso de la arista que va de el nodo i a su padre.

vector<ll> values = {1, 2, 3, 4, 5};

vector<ll> base = hld.build(values);

seg.buildSegmentTree(base, 0, n - 1, seg.tree, 1);

hld.modifyPath(3, 4, 10);

cout << hld.queryPath(3, 4) << '\n';

hld.modifySubtree(1, 2);

cout << hld.querySubtree(1) << '\n';


## Code

```cpp
struct LazySeg
{
    vector<ll> tree, lazyvalues;
    int n;

    LazySeg(int n) : n(n)
    {
        tree.assign((4 * n) + 4, 0);
        lazyvalues.assign((4 * n) + 4, 0);
    }
    // ------------------------------------------------------------------------------------------------------
    //              toma los que si necesites; cambia update y query dependiendo de cuales tomes
    // ------------------------------------------------------------------------------------------------------
    // void buildSegmentTree(vector<ll> &array, ll start, ll end, ll index)
    // {
    //     if (start == end)
    //     {
    //         tree[index] = array[start];
    //         return;
    //     }
    //     else
    //     {
    //         ll mid = (start + end) / 2;
    //         buildSegmentTree(array, start, mid, index * 2);
    //         buildSegmentTree(array, mid + 1, end, (index * 2) + 1);
    //         tree[index] = tree[index * 2] + tree[(index * 2) + 1];
    //         return;
    //     }
    // }
    // ll query(ll startsegment, ll endsegment, ll querystart, ll queryend, ll index)
    // {
    //     if (startsegment >= querystart && endsegment <= queryend)
    //     {
    //         return tree[index];
    //     }
    //     else
    //     {
    //         if (queryend < startsegment || querystart > endsegment)
    //         {
    //             return 0;
    //         }
    //         else
    //         {
    //             ll mid = (startsegment + endsegment) / 2;
    //             ll left = query(startsegment, mid, querystart, queryend, 2 * index);
    //             ll right = query(mid + 1, endsegment, querystart, queryend, (2 * index) + 1);
    //             return left + right;
    //         }
    //     }
    // }

    // void pointupdate(ll startsegment, ll endsegment, ll i, ll incremento, ll index)
    // {
    //     if (i > endsegment || i < startsegment)
    //     {
    //         return;
    //     }
    //     else
    //     {
    //         if (startsegment == endsegment)
    //         {
    //             tree[index] = incremento;
    //             return;
    //         }
    //         else
    //         {
    //             ll mid = (startsegment + endsegment) / 2;
    //             pointupdate(startsegment, mid, i, incremento, 2 * index);
    //             pointupdate(mid + 1, endsegment, i, incremento, (2 * index) + 1);
    //             tree[index] = tree[2 * index] + tree[(2 * index) + 1];
    //             return;
    //         }
    //     }
    // }

    // void Lazyrangeupdate(ll startsegment, ll endsegment, ll l, ll r, ll incremento, ll index)
    // {
    //     if (lazyvalues[index] != 0)
    //     {
    //         tree[index] += (endsegment - startsegment + 1) * lazyvalues[index];
    //         if (startsegment != endsegment)
    //         {
    //             lazyvalues[2 * index] += lazyvalues[index];
    //             lazyvalues[(2 * index) + 1] += lazyvalues[index];
    //         }
    //         lazyvalues[index] = 0;
    //     }
    //     if (startsegment > r || endsegment < l)
    //     {
    //         return;
    //     }
    //     else
    //     {
    //         if (startsegment >= l && endsegment <= r)
    //         {
    //             tree[index] += (endsegment - startsegment + 1) * incremento;
    //             if (startsegment != endsegment)
    //             {
    //                 lazyvalues[2 * index] += incremento;
    //                 lazyvalues[(2 * index) + 1] += incremento;
    //             }
    //             return;
    //         }
    //         else
    //         {
    //             ll mid = (startsegment + endsegment) / 2;
    //             Lazyrangeupdate(startsegment, mid, l, r, incremento, 2 * index);
    //             Lazyrangeupdate(mid + 1, endsegment, l, r, incremento, (2 * index) + 1);
    //             tree[index] = tree[2 * index] + tree[(2 * index) + 1];
    //             return;
    //         }
    //     }
    // }

    // ll lazyquery(ll startsegment, ll endsegment, ll querystart, ll queryend, ll index)
    // {
    //     // resolve lazyvalues sin actualizar
    //     if (lazyvalues[index] != 0)
    //     {
    //         tree[index] += (endsegment - startsegment + 1) * lazyvalues[index];
    //         if (startsegment != endsegment)
    //         {
    //             lazyvalues[2 * index] += lazyvalues[index];
    //             lazyvalues[(2 * index) + 1] += lazyvalues[index];
    //         }
    //         lazyvalues[index] = 0;
    //     }
    //     if (startsegment > queryend || endsegment < querystart)
    //     {
    //         return 0;
    //     }
    //     else
    //     {
    //         if (startsegment >= querystart && endsegment <= queryend)
    //         {
    //             return tree[index];
    //         }
    //         else
    //         {
    //             ll mid = (startsegment + endsegment) / 2;
    //             ll left = lazyquery(startsegment, mid, querystart, queryend, 2 * index);
    //             ll right = lazyquery(mid + 1, endsegment, querystart, queryend, (2 * index) + 1);
    //             return left + right;
    //         }
    //     }
    // }
    void update(int l, int r, ll val)
    {
        Lazyrangeupdate(0, n - 1, l,r, val, 1);
    }

    ll query(int l, int r)
    {
        return query(0, n - 1, l, r, 1);
    }
};

template <bool VALS_IN_EDGES = false>
struct HLD
{
    int n, timer;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, sz;
    LazySeg &seg;

    HLD(int n, LazySeg &seg)
        : n(n), timer(0), adj(n),
          parent(n), depth(n), heavy(n, -1),
          head(n), pos(n), sz(n), seg(seg) {}

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfsSz(int u, int p)
    {
        parent[u] = p;
        sz[u] = 1;
        int maxSubtree = 0;

        for (int v : adj[u])
        {
            if (v == p)
                continue;

            depth[v] = depth[u] + 1;
            int subtree = dfsSz(v, u);
            sz[u] += subtree;
            if (subtree > maxSubtree)
            {
                maxSubtree = subtree;
                heavy[u] = v;
            }
        }
        return sz[u];
    }

    void dfsHld(int u, int h)
    {
        head[u] = h;
        pos[u] = timer++;
        if (heavy[u] != -1)
        {
            dfsHld(heavy[u], h);
        }
        for (int v : adj[u])
        {
            if (v == parent[u] || v == heavy[u])
                continue;
            dfsHld(v, v);
        }
    }
    vector<ll> build(const vector<ll> &values, int root = 0)
    {
        timer = 0;
        depth[root] = 0;
        dfsSz(root, -1);
        dfsHld(root, root);
        vector<ll> base(n);
        for (int u = 0; u < n; u++)
        {
            base[pos[u]] = values[u];
        }
        // Build your existing segment tree using this array.
        return base;
    }

    int lca(int u, int v)
    {
        while (head[u] != head[v])
        {
            if (depth[head[u]] > depth[head[v]])
            {
                u = parent[head[u]];
            }
            else
            {
                v = parent[head[v]];
            }
        }
        return depth[u] < depth[v] ? u : v;
    }

    void modifyPath(int u, int v, ll val)
    {
        while (head[u] != head[v])
        {
            if (depth[head[u]] < depth[head[v]])
            {
                swap(u, v);
            }
            seg.update(pos[head[u]], pos[u], val);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v])
        {
            swap(u, v);
        }
        seg.update(pos[u] + (int)VALS_IN_EDGES, pos[v], val);
    }
    ll queryPath(int u, int v)
    {
        ll ans = 0;

        while (head[u] != head[v])
        {
            if (depth[head[u]] < depth[head[v]])
            {
                swap(u, v);
            }

            ans += seg.query(pos[head[u]], pos[u]);
            u = parent[head[u]];
        }

        if (depth[u] > depth[v])
        {
            swap(u, v);
        }

        ans += seg.query(
            pos[u] + (int)VALS_IN_EDGES,
            pos[v]);

        return ans;
    }

    void modifySubtree(int u, ll val)
    {
        seg.update(pos[u] + (int)VALS_IN_EDGES, pos[u] + sz[u] - 1, val);
    }

    ll querySubtree(int u)
    {
        return seg.query(
            pos[u] + (int)VALS_IN_EDGES,
            pos[u] + sz[u] - 1);
    }
};

```