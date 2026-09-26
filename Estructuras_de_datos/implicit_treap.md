# Implicit Treap

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef struct item *pitem;
struct item
{
   int prior, value, cnt;
   bool rev;
   pitem l, r, padre;
   item(int value) : value(value), prior(rng()), l(NULL), r(NULL), padre(NULL), cnt(0), rev(0) {}
};
vector<pitem> nodos;
int cnt(pitem it)
{
   return it ? it->cnt : 0;
}

void upd_cnt(pitem it)
{
   if (it)
       it->cnt = cnt(it->l) + cnt(it->r) + 1;
}
void update_parent(pitem &t)
{
   if (!t)
       return;
   if (t->l)
       t->l->padre = t;
   if (t->r)
       t->r->padre = t;

   if (t)
   {
       t->padre = NULL;
   }
}

void merge(pitem &t, pitem l, pitem r)
{
   if (!l || !r)
   {
       t = l ? l : r;
   }
   else if (l->prior > r->prior)
   {
       merge(l->r, l->r, r), t = l;
   }
   else
   {
       merge(r->l, l, r->l), t = r;
   }
   update_parent(t);
   upd_cnt(t);
}

void split(pitem t, pitem &l, pitem &r, int key, int add = 0)
{
   if (!t)
       return void(l = r = 0);

   int cur_key = add + cnt(t->l);
   if (t->l)
       t->l->padre = NULL;
   if (t->r)
       t->r->padre = NULL;

   if (key <= cur_key)
   {
       split(t->l, l, t->l, key, add), r = t;
   }
   else
   {
       split(t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
   }
   update_parent(t);
   upd_cnt(t);
}

void output(pitem t)
{
   if (!t)
       return;

   output(t->l);
   cout << t->value + 1 << " ";
   output(t->r);
}

pair<ll, ll> find_raiz_pos(pitem t)
{
   pitem cur = t;
   ll idx = cnt(cur->l);
   while (cur->padre != NULL)
   {
       if (cur == cur->padre->r)
       { // Coming from the right branch
           idx += cnt(cur->padre->l) + 1;
       }
       cur = cur->padre;
   }
   // regresa idx 0-indedxado
   return {cur->value, idx};
}



//uso
pitem root = new item(1);
for (ll i = 2; i <= n; i++)
   {
       merge(root, root, new item(i));
   }

/* split(root,l,r,key)l contiene a los primeros key elementos
 al hacer split, el nodo root no “desaparece” o se borra, sino que 
 se reacomoda dentro del subarbol l o r. 
Al usar vector<pitem>v , para guardar una referencia rapida al nodo, no hace falta cambiar la referencia durante la ejecución de las operaciones. Dado que el nodo no desaparece, sino que solo se reacomoda, la misma referencia que tenga de inicio v[i] seguira siendo durante la ejecución la referencia al nodo i, independientemente de donde quede dentro del treap
*/

```