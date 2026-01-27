//    buildSegmentTree(myvector, 0, myvector.size() - 1, mytree, 1);
// AQUI, PBDS ES DE pair<ll,ll> para manejar "multiset"
void buildSegmentTree(vector<ll> &array, ll start, ll end, vector<PBDS> &tree, ll index)
{
    if (start == end)
    {
        tree[index].insert(make_pair(array[start], start));
        return;
    }
    else
    {
        ll mid = (start + end) / 2;
        buildSegmentTree(array, start, mid, tree, index * 2);
        buildSegmentTree(array, mid + 1, end, tree, (index * 2) + 1);
        //// Si los nodos del arbol tienen un PBDS
        // if (tree[index * 2].size() < tree[(index * 2) + 1].size())
        // {
        //     tree[index] = tree[index * 2 + 1];
        //     for (auto x : tree[index * 2])
        //     {
        //         tree[index].insert(x);
        //     }
        // }
        // else
        // {
        //     tree[index] = tree[index * 2];
        //     for (auto x : tree[(index * 2) + 1])
        //     {
        //         tree[index].insert(x);
        //     }
        // }

        //// si los nodos del arbol tienen un vector:
        // merge(tree[2 * index].begin(), tree[2 * index].end(),
        //       tree[(2 * index) + 1].begin(), tree[(2 * index) + 1].end(),
        //       back_inserter(tree[index]));
        return;
    }
}
// query(mytree, 0, myvector.size() - 1, izqQuery, derQuery, 1)
// buscamos cuantos elementos son mayores que aplha
ll query(vector<PBDS> &tree, ll startsegment, ll endsegment, ll querystart, ll queryend, ll index, pair<ll, ll> aplha)
{
    if (startsegment >= querystart && endsegment <= queryend)
    {
        ////si los nodos del arbol tienen un PBDS. Cuenta los que son mayores que alpha
        ll res = tree[index].size() - tree[index].order_of_key(aplha);
        //// si los nodos del arbol tienen un vector. Cuenta los que son mayores o iguales que alpha:
        // ll res = tree[index].size() - (lower_bound(tree[index].begin(), tree[index].end(), aplha) - tree[index].begin());
        return res;
    }
    else
    {
        if (queryend < startsegment || querystart > endsegment)
        {
            return 0;
        }
        else
        {
            ll mid = (startsegment + endsegment) / 2;
            ll left = query(tree, startsegment, mid, querystart, queryend, 2 * index, aplha);
            ll right = query(tree, mid + 1, endsegment, querystart, queryend, (2 * index) + 1, aplha);
            return left + right;
        }
    }
}

// update de la forma, incrementa/decrementa en x cantidad al elemento i
// pointupdate(tree, 0, myvector.size() - 1, i, x, 1);

void pointupdate(vector<ll> &v, vector<PBDS> &tree, ll startsegment, ll endsegment, ll i, ll nuevo_val, ll index)
{
    if (i > endsegment || i < startsegment)
    {
        return;
    }
    else
    {
        if (startsegment == endsegment)
        {
            tree[index].clear();
            tree[index].insert(make_pair(nuevo_val, i));
            return;
        }
        else
        {
            ll mid = (startsegment + endsegment) / 2;
            pointupdate(v, tree, startsegment, mid, i, nuevo_val, 2 * index);
            pointupdate(v, tree, mid + 1, endsegment, i, nuevo_val, (2 * index) + 1);

            tree[index].erase(make_pair(v[i], i));
            tree[index].insert(make_pair(nuevo_val, i));
            return;
        }
    }
}
void pointupdatehandler(vector<ll> &v, vector<PBDS> &tree, ll startsegment, ll endsegment, ll i, ll nuevo_val, ll index)
{
    pointupdate(v, tree, startsegment, endsegment, i, nuevo_val, index);
    v[i] = nuevo_val;
}