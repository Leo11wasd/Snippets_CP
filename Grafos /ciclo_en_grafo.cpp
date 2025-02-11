bool hayciclo(vector<vector<ll>> &adj, vector<ll> &visitados, ll actual)
{
    visitados[actual] = 1;
    for (ll x : adj[actual])
    {
        if (visitados[x] == 1)
        {
            return 1;
        }
        else if (visitados[x] == 0)
        {

            bool h = hayciclo(adj, visitados, x);
            if (h)
            {
                return 1;
            }
        }
    }
    visitados[actual] = 2;
    return false;
}


/*
//ESTO VA DENTRO DEL MAIN
 bool ciclo = 0;
        vector<ll> visitados(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (visitados[i] == 0)
            {
                // no lo he visitado, visitemoslo
                ciclo |= hayciclo(adj, visitados, i);
            }
        }
*/