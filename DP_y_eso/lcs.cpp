string longest_common_subsequence(string s1, string s2)
{
    ll n1 = s1.size();
    ll n2 = s2.size();
    ll dp[n1 + 2][n2 + 2];
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n1; i++)
    {
        for (int j = 1; j <= n2; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    //dp[n1][n2]=la longitud de la subsecuencia
    ll i, j;
    i = n1;
    j = n2;
    string res = "";
    while (i > 0 && j > 0)
    {
        if (dp[i][j] == dp[i - 1][j])
        {
            // cout<<"up"<<endl;
            i--;
        }
        else if (dp[i][j] == dp[i][j - 1])
        {
            // cout<<"izq"<<endl;
            j--;
        }
        else if (dp[i][j] == dp[i - 1][j - 1])
        {
            // cout<<"diagonal sin"<<endl;
            i--;
            j--;
        }
        else
        {
            // cout<<"diagonal con"<<endl;
            res = s2[j - 1] + res;
            i--;
            j--;
        }
    }

    return res;
}
