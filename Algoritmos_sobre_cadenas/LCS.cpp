int longestCommonSubsequence(string text1, string text2)
    {
        int n, m;
        n = text1.size();
        m = text2.size();
        vector<int> actual(m + 1), previo;
        previo.assign(m + 1, 0);
        for (int i = 0; i < n; i++)
        {
            actual[0] = 0;
            for (int j = 1; j <= m; j++)
            {
                if (text1[i] == text2[j - 1])
                {
                    actual[j] = 1 + previo[j - 1];
                }
                else
                {
                    actual[j] = max(actual[j - 1], previo[j]);
                }
            }
            previo = actual;
        }

        return actual[m];
    }