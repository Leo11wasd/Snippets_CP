# Mo's algorithm

Whenever we have a problem for which we have to answer range queries over some array, we can do the following :
- Expand the subarray: Get the answer for some subarray **[l-1,r]** or **[l,r+1]** from the array **[l,r]**;(ideally in **O(1)** time)
- Contract the subarray: Get the answer for some subarray **[l+1,r]** or **[l,r-1]** from the array **[l,r]**; (ideally in **O(1)** time)
- The queries can be answered offline

We can sort the queries in some intelligent way such that it enables us to answer them using only contraction and expansion operations.

We can split the array in blocks of size $\sqrt{N}$ and answer the queries depending on which block they start in.

We will first answer all queries which have the left index in block 0, then answer all queries which have left index in block 1 and so on. And also we will have to answer the queries of a block in a special order, namely sorted by the right index of the queries.



## Complexity

- Time:$O((N+Q)\sqrt{N})$

## Notes

- https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm

## Code

```cpp
void remove(ll idx, vector<ll> &v) {}
void add(ll idx, vector<ll> &v) {}
ll get_answer() {}

ll block_size; // no olvides inicializarlo en sqrt(n)

struct Query
{
    ll l, r, idx;
    bool operator<(Query other) const
    {
        if (l / block_size != other.l / block_size)
            return l / block_size < other.l / block_size;
        return ((l / block_size) & 1) ? (r > other.r) : (r < other.r);
    }
};

vector<ll> mo_s_algorithm(vector<Query> queries, vector<ll> &v)
{
    vector<ll> answers(queries.size());
    sort(queries.begin(), queries.end());

    // TODO: initialize data structure

    ll cur_l = 0;
    ll cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries)
    {
        while (cur_l > q.l)
        {
            cur_l--;
            add(cur_l, v);
        }
        while (cur_r < q.r)
        {
            cur_r++;
            add(cur_r, v);
        }
        while (cur_l < q.l)
        {
            remove(cur_l, v);
            cur_l++;
        }
        while (cur_r > q.r)
        {
            remove(cur_r, v);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}
```