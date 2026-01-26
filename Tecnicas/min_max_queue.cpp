//push pop y obtener el maximo/minimo O(1) amortizado
// stack<pair<ll, ll>> s1, s2;

ll maximo_f(stack<pair<ll, ll>> &s1, stack<pair<ll, ll>> &s2)
{
    ll maximo;
    if (s1.empty() || s2.empty())
        maximo = s1.empty() ? s2.top().second : s1.top().second;
    else
        maximo = max(s1.top().second, s2.top().second);
    return maximo;
}

void agrega(stack<pair<ll, ll>> &s1, stack<pair<ll, ll>> &s2, ll new_element)
{
    ll maximo = s1.empty() ? new_element : max(new_element, s1.top().second);
    s1.push({new_element, maximo});
}

void elimina(stack<pair<ll, ll>> &s1, stack<pair<ll, ll>> &s2)
{
    if (s2.empty())
    {
        while (!s1.empty())
        {
            ll element = s1.top().first;
            s1.pop();
            ll maximo = s2.empty() ? element : max(element, s2.top().second);
            s2.push({element, maximo});
        }
    }
    // ll remove_element = s2.top().first;
    s2.pop();
}