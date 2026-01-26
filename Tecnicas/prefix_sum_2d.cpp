ll cuadrado(vector<vector<ll>> &pref, ll x, ll y, ll x2, ll y2)
{
  ll val = pref[x2][y2];
  bool cx, cy;
  cx = cy = false;
  if (x - 1 >= 0)
  {
    val -= pref[x - 1][y2];
    cx = true;
  }
  if (y - 1 >= 0)
  {
    val -= pref[x2][y - 1];
    cy = true;
  }
  if (cx && cy)
  {

    val += pref[x - 1][y - 1];
  }
  return val;
}

    // creamos la matriz para las prefix querys
    for (int i = 0; i < n; i++)
    {
        pref[i][0] = mat[i][0];
        for (int j = 1; j < m; j++)
        {
            pref[i][j] = pref[i][j - 1] + mat[i][j];
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            pref[i][j] += pref[i - 1][j];
        }
    }