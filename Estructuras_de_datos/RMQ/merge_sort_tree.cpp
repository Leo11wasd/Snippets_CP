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
        return;
    }
}
// query(mytree, 0, myvector.size() - 1, izqQuery, derQuery, 1)
// buscamos cuantos elementos son mayores que aplha
ll query(vector<PBDS> &tree, ll startsegment, ll endsegment, ll querystart, ll queryend, ll index, pair<ll, ll> aplha)
{
    if (startsegment >= querystart && endsegment <= queryend)
    {
        ll res = tree[index].size() - tree[index].order_of_key(aplha);
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