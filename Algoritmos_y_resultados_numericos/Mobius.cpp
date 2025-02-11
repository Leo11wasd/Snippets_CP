ll N = 100005;
vector<ll> a(N, 1), prime_count(N, 0), m(N);
void mobius()
{
    for (int i = 2; i < N; i++)
    {
        if (prime_count[i] == 0)
        {
            for (int j = i; j < N; j += i)
            {
                prime_count[j]++;
                a[j] *= i;
            }
        }
    }
    for (int i = 1; i < N; i++)
    {
        if (a[i] == i)
        {
            if (prime_count[i] & 1)
            {
                m[i] = -1;
            }
            else
            {
                m[i] = 1;
            }
        }
        else
        {
            m[i] = 0;
        }
    }
}