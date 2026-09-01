# Persistent Segment Tree

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
struct Vertex
{
   Vertex *l, *r;
   ll sum;
   Vertex(ll val) : l(nullptr), r(nullptr), sum(val) {}
   Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0)
   {
       if (l)
           sum += l->sum;
       if (r)
           sum += r->sum;
   }
};
Vertex *build(vector<ll> &a, ll tl, ll tr)
{
   if (tl == tr)
       return new Vertex(a[tl]);
   ll tm = (tl + tr) / 2;
   return new Vertex(build(a, tl, tm), build(a, tm + 1, tr));
}
ll get_sum(Vertex *v, ll tl, ll tr, ll l, ll r)
{
   if (l > r)
       return 0;
   if (l == tl && tr == r)
       return v->sum;
   ll tm = (tl + tr) / 2;
   return get_sum(v->l, tl, tm, l, min(r, tm)) + get_sum(v->r, tm + 1, tr, max(l, tm + 1), r);
}
Vertex *update(Vertex *v, ll tl, ll tr, ll pos, ll new_val)
{
   if (tl == tr)
       return new Vertex(new_val);
   ll tm = (tl + tr) / 2;
   if (pos <= tm)
       return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
   else
       return new Vertex(v->l, update(v->r, tm + 1, tr, pos, new_val));
}

// uso:
vector<Vertex> l;
l.push_back(*build(v, 0, n - 1));
*update(&l[k], 0, n - 1, a, x);
get_sum(&l[k], 0, n - 1, a, b)



FENWICK TREE (BINARY INDEXED TREE) 
para range sum queries con updates
struct FenwickTreeRange
{
   // 1-indexados
   vector<int> bit1, bit2; // binary indexed trees
   int n;
   FenwickTreeRange(int n)
   {
       this->n = n;
       bit1.assign(n + 1, 0);
       bit2.assign(n + 1, 0);
   }
   void add(vector<int> &bit, int idx, int x)
   {
       while (idx <= n)
       {
           bit[idx] += x;
           idx += idx & -idx;
       }
   }

   void range_add(int l, int r, int x)
   {
       add(bit1, l, x);
       add(bit1, r + 1, -x);
       add(bit2, l, x * (l - 1));
       add(bit2, r + 1, -x * r);
   }

   int sum(vector<int> &bit, int idx)
   {
       int total = 0;
       while (idx > 0)
       {
           total += bit[idx];
           idx -= idx & -idx;
       }
       return total;
   }
   int prefix_sum(int idx)
   {
       return sum(bit1, idx) * idx - sum(bit2, idx);
   }

   int range_sum(int l, int r)
   {
       return prefix_sum(r) - prefix_sum(l - 1);
   }
};

```