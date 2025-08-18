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