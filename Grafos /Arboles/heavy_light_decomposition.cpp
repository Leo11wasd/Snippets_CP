/*USO:
TODO 0-INDEXADO
vector<ll>vals(n);
hld h = {n, ceil(log2(n))};
h.init_arrays();
h.add_edge(a, b);
h.init_tree(vals);
res = h.query(u, v);
h.update(u, v, valor);
*/
struct hld
{
    int N;
    int lg;
    int label_time;
    vector<int> bigchild, sz, depth, chain, label, par;
    vector<vector<int>> lca_lift, edges;
    vector<ll> seg_tree, seg_lazy;

    /* ----------- segment tree ----------- */

    /* CHANGE THIS SECTION BY PROBLEM */
    inline ll seg_combine(ll a, ll b)
    {
        // como se combinan segmentos contiguos (query)
        return a + b;
    }

    inline ll seg_lazy_apply(ll lazy_val, ll new_val)
    {
        // como se actualizan/acumulan lazy values ante un update
        return new_val;
    }

    inline ll seg_lazy_func(ll cur_val, ll lazy_val, int l, int r)
    {
        // como se aplica un lazy value pendiente a un intervalo l,r.
        return lazy_val;
    }
    // valor default para cuando la consulta esta fuera de rango
    const ll seg_sentinel = 0;
    // identificador de cuando no hay updates pendientes (lazy values)
    const ll seg_lazy_sentinel = -1;
    // valores iniciales de los segment tree. Luego se puede asignar valores con init_tree despues
    const ll seg_init_val = 0;
    /* END SECTION */

    ll seg_query_header(int l, int r)
    {
        return seg_query_rec(0, 0, N - 1, l, r);
    }

    ll seg_query_rec(int i, int tl, int tr, int ql, int qr)
    {
        seg_eval_lazy(i, tl, tr);

        if (ql <= tl && tr <= qr)
            return seg_tree[i];
        if (tl > tr || tr < ql || qr < tl)
            return seg_sentinel;

        int mid = (tl + tr) / 2;
        ll a = seg_query_rec(2 * i + 1, tl, mid, ql, qr);
        ll b = seg_query_rec(2 * i + 2, mid + 1, tr, ql, qr);
        return seg_combine(a, b);
    }

    void seg_update_header(int l, int r, ll v)
    {
        seg_update_rec(0, 0, N - 1, l, r, v);
    }

    ll seg_update_rec(int i, int tl, int tr, int ql, int qr, ll v)
    {
        seg_eval_lazy(i, tl, tr);

        if (tl > tr || tr < ql || qr < tl)
            return seg_tree[i];
        if (ql <= tl && tr <= qr)
        {
            seg_lazy[i] = seg_lazy_apply(seg_lazy[i], v);
            seg_eval_lazy(i, tl, tr);
            return seg_tree[i];
        }
        if (tl == tr)
            return seg_tree[i];

        int mid = (tl + tr) / 2;
        ll a = seg_update_rec(2 * i + 1, tl, mid, ql, qr, v);
        ll b = seg_update_rec(2 * i + 2, mid + 1, tr, ql, qr, v);
        return seg_tree[i] = seg_combine(a, b);
    }

    void seg_eval_lazy(int i, int l, int r)
    {
        if (seg_lazy[i] == seg_lazy_sentinel)
            return;

        seg_tree[i] = seg_lazy_func(seg_tree[i], seg_lazy[i], l, r);

        if (l != r)
        {
            seg_lazy[i * 2 + 1] = seg_lazy_apply(seg_lazy[i * 2 + 1], seg_lazy[i]);
            seg_lazy[i * 2 + 2] = seg_lazy_apply(seg_lazy[i * 2 + 2], seg_lazy[i]);
        }

        seg_lazy[i] = seg_lazy_sentinel;
    }

    /* ----------- init phase 1 ----------- */
    /* initialize segtree, clear edges, etc. */
    void init_arrays()
    {
        // everything not initialized doesn't need to be
        bigchild.resize(N);
        sz.resize(N);
        depth.resize(N);
        chain.resize(N);
        label.resize(N);
        par.resize(N);

        edges.resize(N, vector<int>());
        lca_lift.resize(N, vector<int>(lg));
        seg_tree.resize(4 * N);
        seg_lazy.resize(4 * N);

        for (int i = 0; i < N; i++)
        {
            edges[i].clear();
            chain[i] = i;
        }

        for (int i = 0; i < 4 * N; i++)
        {
            seg_tree[i] = seg_init_val;
            seg_lazy[i] = seg_lazy_sentinel;
        }
    }

    /* ----------- init phase 2 ----------- */
    /* put edges in */

    void add_edge(int u, int v)
    {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    /* ----------- init phase 3 ----------- */
    /* build the lca and hld stuff */

    void init_tree(vector<ll> &arr, int root = 0)
    {
        // lca
        lca_dfs(root, -1);

        // size, compute biggest children
        dfs_size(root, -1, 0);

        // compute chains
        dfs_chains(root, -1);

        // label nodes
        label_time = 0;
        dfs_labels(arr, root, -1);
    }

    void lca_dfs(int v, int par)
    {
        lca_lift[v][0] = par;

        for (int i = 1; i < lg; i++)
        {
            if (lca_lift[v][i - 1] == -1)
                lca_lift[v][i] = -1;
            else
                lca_lift[v][i] = lca_lift[lca_lift[v][i - 1]][i - 1];
        }

        for (int x : edges[v])
        {
            if (x != par)
            {
                lca_dfs(x, v);
            }
        }
    }

    void dfs_size(int v, int p, int d)
    {
        sz[v] = 1;
        depth[v] = d;
        par[v] = p;
        int bigc = -1, bigv = -1;

        for (int x : edges[v])
        {
            if (x != p)
            {
                dfs_size(x, v, d + 1);
                sz[v] += sz[x];
                if (sz[x] > bigv)
                {
                    bigc = x;
                    bigv = sz[x];
                }
            }
        }

        bigchild[v] = bigc;
    }

    void dfs_chains(int v, int p)
    {
        if (bigchild[v] != -1)
        {
            chain[bigchild[v]] = chain[v];
        }

        for (int x : edges[v])
        {
            if (x != p)
            {
                dfs_chains(x, v);
            }
        }
    }

    void dfs_labels(vector<ll> &arr, int v, int p)
    {
        label[v] = label_time++;
        seg_update_header(label[v], label[v], arr[v]);

        if (bigchild[v] != -1)
        {
            dfs_labels(arr, bigchild[v], v);
        }

        for (int x : edges[v])
        {
            if (x != p && x != bigchild[v])
            {
                dfs_labels(arr, x, v);
            }
        }
    }

    /* ----------- init phase 4 ----------- */
    /* usage */

    int lca(int a, int b)
    {
        if (depth[a] < depth[b])
            swap(a, b);
        int d = depth[a] - depth[b];
        int v = get_kth_ancestor(a, d);
        if (v == b)
        {
            return v;
        }
        else
        {
            for (int i = lg - 1; i >= 0; i--)
            {
                if (lca_lift[v][i] != lca_lift[b][i])
                {
                    v = lca_lift[v][i];
                    b = lca_lift[b][i];
                }
            }
            return lca_lift[b][0];
        }
    }

    int get_kth_ancestor(int v, int k)
    {
        for (int i = lg - 1; i >= 0; i--)
        {
            if (v == -1)
                return v;
            if ((1 << i) <= k)
            {
                v = lca_lift[v][i];
                k -= (1 << i);
            }
        }
        return v;
    }

    /* excludes p */
    ll query_chain(int v, int p)
    {
        ll val = seg_sentinel;
        while (depth[p] < depth[v])
        {
            int top = chain[v];
            if (depth[top] <= depth[p])
            {
                int diff = depth[v] - depth[p];
                top = get_kth_ancestor(v, diff - 1);
            }
            val = seg_combine(val, seg_query_header(label[top], label[v]));
            v = par[top];
        }
        return val;
    }

    ll query(int u, int v)
    {
        int lc = lca(u, v);
        ll val = seg_combine(query_chain(u, lc), query_chain(v, lc));
        return seg_combine(val, seg_query_header(label[lc], label[lc]));
    }

    /* excludes p */
    void update_chain(int v, int p, ll val)
    {
        while (depth[p] < depth[v])
        {
            int top = chain[v];
            if (depth[top] <= depth[p])
            {
                int diff = depth[v] - depth[p];
                top = get_kth_ancestor(v, diff - 1);
            }
            seg_update_header(label[top], label[v], val);
            v = par[top];
        }
    }

    void update(int u, int v, ll val)
    {
        int lc = lca(u, v);
        update_chain(u, lc, val);
        update_chain(v, lc, val);
        seg_update_header(label[lc], label[lc], val);
    }
};