// recuerda inicializar vector<ll> lazyvalues((4*n)+1,0) en el solved()
void Lazyrangeupdate(vector<ll> &tree, vector<ll> &lazyvalues, ll startsegment, ll endsegment, ll l, ll r, ll incremento, ll index)
{
    // primero, resolve lazyvalues antes de bajar
    if (lazyvalues[index] != 0)
    {
        tree[index] += lazyvalues[index];
        // si no es nodo hoja, pasale el lazy value a los hijos
        if (startsegment != endsegment)
        {
            lazyvalues[2 * index] += lazyvalues[index];
            lazyvalues[(2 * index) + 1] += lazyvalues[index];
        }
        // ya quedo el lazyvalue resuelto
        lazyvalues[index] = 0;
    }
    if (startsegment > r || endsegment < l)
    {
        return;
    }
    else
    {
        if (startsegment >= l && endsegment <= r)
        {
            // complete overlap
            tree[index] += incremento;
            if (startsegment != endsegment)
            {
                // cambia el lazyvalue de sus hijos si esque tiene
                // esta es la optimización xd
                lazyvalues[2 * index] += incremento;
                lazyvalues[(2 * index) + 1] += incremento;
            }
            return;
        }
        else
        {
            ll mid = (startsegment + endsegment) / 2;
            Lazyrangeupdate(tree, lazyvalues, startsegment, mid, l, r, incremento, 2 * index);
            Lazyrangeupdate(tree, lazyvalues, mid + 1, endsegment, l, r, incremento, (2 * index) + 1);
            // update el actual
            //  AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            tree[index] = min(tree[2 * index], tree[(2 * index) + 1]);
            return;
        }
    }
}

ll lazyquery(vector<ll> &tree, vector<ll> &lazyvalues, ll startsegment, ll endsegment, ll querystart, ll queryend, ll index)
{
    // resolve lazyvalues sin actualizar
    if (lazyvalues[index] != 0)
    {
        tree[index] += lazyvalues[index];
        // si no es nodo hoja, pasale el lazy value a los hijos
        if (startsegment != endsegment)
        {
            lazyvalues[2 * index] += lazyvalues[index];
            lazyvalues[(2 * index) + 1] += lazyvalues[index];
        }
        // ya quedo el lazyvalue resuelto
        lazyvalues[index] = 0;
    }

    // no overlap
    if (startsegment > queryend || endsegment < querystart)
    {
        return mx;
    }
    else
    {
        // full overlap

        if (startsegment >= querystart && endsegment <= queryend)
        {
            return tree[index];
        }
        else
        {
            // partial overlap
            ll mid = (startsegment + endsegment) / 2;
            ll left = lazyquery(tree, lazyvalues, startsegment, mid, querystart, queryend, 2 * index);
            ll right = lazyquery(tree, lazyvalues, mid + 1, endsegment, querystart, queryend, (2 * index) + 1);
            //  AQUI ES DÓNDE SE CAMBIA DEPENDIENDO DEL TIPO DE CONSULTA
            return min(left, right);
        }
    }
}