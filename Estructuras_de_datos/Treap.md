# Treap

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct item
{
   int key, prior;
   item *l, *r;
   item() {}
   item(int key) : key(key), prior(rng()), l(NULL), r(NULL) {}
   item(int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) {}
};
typedef item *pitem;

void split(pitem t, int key, pitem &l, pitem &r)
{
   if (!t)
       l = r = NULL;
   else if (t->key < key)
       split(t->r, key, t->r, r), l = t;
   else
       split(t->l, key, l, t->l), r = t;
}
void insert(pitem &t, pitem it)
{
   if (!t)
       t = it;
   else if (it->prior > t->prior)
       split(t, it->key, it->l, it->r), t = it;
   else
       insert(t->key <= it->key ? t->r : t->l, it);
}

void merge(pitem &t, pitem l, pitem r)
{
   if (!l || !r)
       t = l ? l : r;
   else if (l->prior > r->prior)
       merge(l->r, l->r, r), t = l;
   else
       merge(r->l, l, r->l), t = r;
}

void erase(pitem &t, int key)
{
   if (t->key == key)
   {
       pitem th = t;
       merge(t, t->l, t->r);
       delete th;
   }
   else
       erase(key < t->key ? t->l : t->r, key);
}

pitem unite(pitem l, pitem r)
{
   if (!l || !r)
       return l ? l : r;
   if (l->prior < r->prior)
       swap(l, r);
   pitem lt, rt;
   split(r, l->key, lt, rt);
   l->l = unite(l->l, lt);
   l->r = unite(l->r, rt);
   return l;
}

void dfs(pitem &t, vector<ll> &v, ll n, ll x)
{
   if (t == NULL)
   {
       return;
   }
   v[t->key] = x;
   dfs(t->l, v, n, x);
   dfs(t->r, v, n, x);
}
// USO
// declaración de un arreglo de treaps. usamos pitem para crearlos
vector<pitem> treaps(101, {});
pitem a, b, c, d;
for (int i = 0; i < n; i++)
{
   // merge asume que todos los elementos del treap l de entrada tienen key menor que todos los elementos del treap r de entrada
   //  si no se puede asegurar esa relacion, hay que usar unite
   merge(treaps[x], treaps[x], new item(v[i]));
}

// almacenar en c a todos los elementos del treap treaps[x] con llave entre [l , r]
// al hacer split(a,x,b,c), el treap a se parte en dos treaps b y c. En b quedan todos los nodos con key < x
// y en c quedan todos los nodos con key >= x
split(treaps[x], l - 1, a, b);
split(b, r, c, d);


```