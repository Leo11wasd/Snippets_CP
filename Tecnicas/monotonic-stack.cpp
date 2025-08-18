// encontrar la cantidad de elementos consecutivos en
// los que cada elemento de v[i] es el mínimo. Si se quiere el intervalo
// en el que se es el máximo, mete al stack como base {mx,-1} o {mx,n}
// y cambia las desigualdades de los whiles
// izquierda[i]=cantidad de elementos a la izquierda menores estricto que v[i]+1 (el mismo)
// derecha[i]=cantidad de elementos a la derecha menores que v[i]+1 (el mismo)
stack<pair<ll, ll>> s;
s.push({mn, -1});
for (int i = 0; i < n; i++)
{
    while (v[i] < s.top().first)
    {
        s.pop();
    }
    izquierda[i] = i - s.top().second;
    s.push({v[i], i});
}
while (!s.empty())
{
    s.pop();
}
s.push({mn, n});

for (int i = n - 1; i >= 0; i--)
{
    while (v[i] <= s.top().first)
    {
        s.pop();
    }
    derecha[i] = s.top().second - i;
    s.push({v[i], i});
}