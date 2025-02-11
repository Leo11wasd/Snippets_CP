// Construcción del arreglo LPS
void buildLPS(string &pattern, vector<ll> &lps)
{
    ll m = pattern.size();
    ll len = 0; // Longitud del prefijo más largo que es también sufijo
    ll i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Búsqueda de un patrón en una secuencia usando KMP
// Al final, el arreglo ocurrences guarda los indices dónde sucedio una ocurrencia del patron en la cadena "sequence"

vector<ll> knuthMorrisPratt(string &sequence, string &pattern)
{
    ll n = sequence.size();
    ll m = pattern.size();
    vector<ll> lps(n, 0);
    buildLPS(pattern, lps); // Construir el arreglo LPS
    vector<ll> occurrences; // Almacenar los índices de las apariciones del patrón

    ll i = 0; // Índice para la secuencia
    ll j = 0; // Índice para el patrón

    while (i < n)
    {
        if (sequence[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {                                 // Patrón encontrado
            occurrences.push_back(i - j); // Guardar el índice donde comienza el patrón
            j = lps[j - 1];               // Reiniciar usando LPS
        }
        else if (i < n && sequence[i] != pattern[j])
        {
            if (j != 0)
            {
                j = lps[j - 1]; // Reiniciar usando LPS
            }
            else
            {
                i++;
            }
        }
    }
    return occurrences;
}