//    buildSegmentTree(myvector, 0, myvector.size() - 1, mytree, 1);
void buildSegmentTree(vector<ll> &array, ll start, ll end, vector<multiset<ll>> &tree, ll index)
{
    if (start == end)
    {
        tree[index] = {array[start]};
        return;
    }
    else
    {
        ll mid = (start + end) / 2;
        // izquierda
        buildSegmentTree(array, start, mid, tree, index * 2);
        // derecha
        buildSegmentTree(array, mid + 1, end, tree, (index * 2) + 1);
        // aqui tomamos el minimo( pa min range queries); si se ocupa
        // ACA SE CAMBIA EL TIPO DE CONSULTA
        merge(tree[index * 2].begin(), tree[index * 2].end(), tree[(index * 2) + 1].begin(), tree[(index * 2) + 1].end(), inserter(tree[index], tree[index].begin()));
        return;
    }
}
// query(mytree, 0, myvector.size() - 1, izqQuery, derQuery, 1)
// buscamos al elemento más pequeño que sea mayor que aplha
ll query(vector<multiset<ll>> &tree, ll startsegment, ll endsegment, ll querystart, ll queryend, ll index, ll aplha)
{
    // complete overlap
    if (startsegment >= querystart && endsegment <= queryend)
    {
        ll res;
        if (upper_bound(tree[index].begin(), tree[index].end(), aplha) == tree[index].end())
        {
            res = -1;
        }
        else
        {
            res = *upper_bound(tree[index].begin(), tree[index].end(), aplha);
        }
        return res;
    }
    else
    {
        // no overlap
        if (queryend < startsegment || querystart > endsegment)
        {
            //  AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            return -1;
        }
        else
        {
            // partial overlap
            ll mid = (startsegment + endsegment) / 2;
            ll left = query(tree, startsegment, mid, querystart, queryend, 2 * index, aplha);
            ll right = query(tree, mid + 1, endsegment, querystart, queryend, (2 * index) + 1, aplha);
            // AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            if (left != -1 && right != -1)
            {
                return min(left, right);
            }
            else
            {
                return max(left, right);
            }
        }
    }
}
// update de la forma, incrementa/decrementa en x cantidad al elemento i
// pointupdate(tree, 0, myvector.size() - 1, i, x, 1);

void pointupdate(vector<ll> &v, vector<multiset<ll>> &tree, ll startsegment, ll endsegment, ll i, ll incremento, ll index)
{
    if (i > endsegment || i < startsegment)
    {
        return;
    }
    else
    {
        if (startsegment == endsegment)
        {
            //  AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            tree[index] = {incremento};
            return;
        }
        else
        {
            ll mid = (startsegment + endsegment) / 2;
            pointupdate(v, tree, startsegment, mid, i, incremento, 2 * index);
            pointupdate(v, tree, mid + 1, endsegment, i, incremento, (2 * index) + 1);
            //  AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            tree[index].erase(tree[index].find(v[i]));
            tree[index].insert(incremento);
            return;
        }
    }
}
void pointupdatehandler(vector<ll> &v, vector<multiset<ll>> &tree, ll startsegment, ll endsegment, ll i, ll incremento, ll index)
{
    pointupdate(v, tree, startsegment, endsegment, i, incremento, index);
    v[i] = incremento;
}