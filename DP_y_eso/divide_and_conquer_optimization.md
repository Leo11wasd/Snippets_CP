# Divide and conquer dp optimization

## Complexity

- Time: $O(kn\log {n})$
- Memory:

## Notes

### How to recognize Divide & Conquer DP Optimization

A common form is:

$$

dp[k][i] = \min_{j<i}{dp[k-1][j] + cost(j,i)}

$$
where we want to compute the DP for (k) groups/segments and (i) positions.

The key question is whether the **optimal transition point is monotonic**:
$$

opt[k][i] \le opt[k][i+1].

$$
In other words, as (i) increases, the value of (j) giving the best transition never moves to the left.

If this property holds, we can compute a whole DP row with divide and conquer:

* Compute the answer for the midpoint (mid).
* Only search (j) inside the range ([optL,optR]).
* Once the best (j=opt) is found:

  * recursively solve the left half with (j\in[optL,opt])
  * recursively solve the right half with (j\in[opt,optR]).

This reduces the complexity of one row from (O(n^2)) to roughly (O(n\log n)), giving (O(kn\log n)) overall.

**Recognition checklist:**

1. The DP has the form `dp[k][i] = min/max over j < i`.
2. There are many possible transition points (j), making the naive solution (O(kn^2)).
3. The cost of a transition `cost(j,i)` can be computed efficiently.
4. Most importantly, the optimal (j) is **monotonic** as (i) increases.

The monotonicity usually follows from a property of `cost`, often related to the **quadrangle inequality / Monge property**. If you can prove that, Divide & Conquer DP optimization is a strong candidate.


## Code

```cpp
void dnc(int k, int l, int r, int optl, int optr)
{
    if (l > r)
        return;
 
    int mid = l + ((r - l) / 2);
    // pair<int, int> best = {1e17, optl};
    int best, idx;
    best = dp[optl][k - 1] + func[optl + 1][mid];
    idx = optl;
    for (int i = optl; i <= min(mid - 1, optr); i++)
    {
        if (best > dp[i][k - 1] + func[i + 1][mid])
        {
            best = dp[i][k - 1] + func[i + 1][mid];
            idx = i;
        }
    }
 
    dp[mid][k] = best;
 
    dnc(k, l, mid - 1, optl, idx);
    dnc(k, mid + 1, r, idx, optr);
}


//en main, precalculamos dp[i][1]
for (int i = 0; i < n; i++)
{
    dp[i][1] = func[0][i];
}
//calculamos el resto
for (int i = 2; i <= k; i++)
{
    dnc(i, 0, n - 1, 0, n - 2);
}
//imprimimos res
cout << dp[n - 1][k] << "\n";

 
```