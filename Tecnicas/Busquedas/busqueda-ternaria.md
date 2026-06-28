# Ternary search

The typical formulation of a problem which can be solved through ternary search is the following: Given a convex function, find its minimum/maximum.
Univariate convex functions are u or n shaped functions. They satisfy $f(x-\epsilon)\leq f(x) \geq f(x+\epsilon)$ or $f(x-\epsilon)\geq f(x) \leq f(x+\epsilon)$ for a unique value x.

For CP problems, The evaluation of $f(x)$ is usually cheap/easy to implement but its not feasable to calculate it for all x values in some range of interest. If we now that our function is convex, we can find $x$ using a similar approach as the binary search one: Choose two element $m_1,m_2 \in [L,R]$ the current range. Evaluate $f(m_1) and f(m_2)$ and check whether $f(m_1)<f(m_2)$. Shorten the range depending on the result and the shape of $f$.

## Complexity

- Time: $O(\log_3{N})$

## Notes

- https://cp-algorithms.com/num_methods/ternary_search.html

## Code

```cpp
double ternary_search(double l, double r)
{
    // en lugar de eps, se pueden realizar iteraciones
    // para limites de precisión de 10^-6
    // 200 o 300 iteraciones suelen ser susficientes
    double eps = 1e-9; // limite del error
    double m1, m2, f1, f2;
    while (r - l > eps)
    {
        m1 = l + (r - l) / 3;
        m2 = r - (r - l) / 3;
        // evaluar la funcion en los dos puntos
        f1 = func(m1);
        f2 = func(m2);
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return func(l);
}
// sobre un espacio entero
ll lo = -1, hi = n;
while (hi - lo > 1)
{
    ll mid = (hi + lo) >> 1;
    if (f(mid) > f(mid + 1))
        hi = mid;
    else
        lo = mid;
}
// lo + 1 is the answer
```