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
