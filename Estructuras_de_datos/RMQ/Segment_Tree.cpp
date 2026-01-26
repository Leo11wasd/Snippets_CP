
//    buildSegmentTree(myvector, 0, myvector.size() - 1, mytree, 1);
void buildSegmentTree(vector<ll> &array, ll start, ll end, vector<ll> &tree, ll index)
{
    if (start == end)
    {
        tree[index] = array[start];
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
        tree[index] = min(tree[index * 2], tree[(index * 2) + 1]);
        return;
    }
}
// query(mytree, 0, myvector.size() - 1, izqQuery, derQuery, 1)
ll query(vector<ll> &tree, ll startsegment, ll endsegment, ll querystart, ll queryend, ll index)
{
    // complete overlap
    if (startsegment >= querystart && endsegment <= queryend)
    {
        return tree[index];
    }
    else
    {
        // no overlap
        if (queryend < startsegment || querystart > endsegment)
        {
            //  AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            return mx;
        }
        else
        {
            // partial overlap
            ll mid = (startsegment + endsegment) / 2;
            ll left = query(tree, startsegment, mid, querystart, queryend, 2 * index);
            ll right = query(tree, mid + 1, endsegment, querystart, queryend, (2 * index) + 1);
            // AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            return min(left, right);
        }
    }
}
// update de la forma, incrementa/decrementa en x cantidad al elemento i
// pointupdate(tree, 0, myvector.size() - 1, i, x, 1);
void pointupdate(vector<ll> &tree, ll startsegment, ll endsegment, ll i, ll incremento, ll index)
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
            tree[index] += incremento;
            return;
        }
        else
        {
            ll mid = (startsegment + endsegment) / 2;
            pointupdate(tree, startsegment, mid, i, incremento, 2 * index);
            pointupdate(tree, mid + 1, endsegment, i, incremento, (2 * index) + 1);
            //  AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            tree[index] = min(tree[2 * index], tree[(2 * index) + 1]);
            return;
        }
    }
}
//update de la forma, incrementa/decrementa en x cantidad todos los elementos
//entre left y right
//  rangeupdate(tree,0,myvector.size() - 1,left,right,x,1);
void rangeupdate(vector<ll> &tree, ll startsegment, ll endsegment, ll l, ll r, ll incremento, ll index)
{   
    if (l > endsegment || r < startsegment)
    {
        return;
    }
    else
    {
        if (endsegment == startsegment)
        {
            tree[index] += incremento;
            return;
        }
        else
        {
            ll mid = (startsegment + endsegment) / 2;
            rangeupdate(tree,startsegment,mid,l,r,incremento,2*index);
            rangeupdate(tree,mid+1,endsegment,l,r,incremento,(2*index)+1);
            tree[index]=min(tree[2*index],tree[(2*index)+1]);
            return;
        }
    }
}