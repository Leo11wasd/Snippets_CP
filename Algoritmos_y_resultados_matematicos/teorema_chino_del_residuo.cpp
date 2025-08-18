using T = __int128;
// ax + by = __gcd(a, b)
// returns __gcd(a, b)
T extended_euclid(T a, T b, T &x, T &y)
{
    T xx = y = 0;
    T yy = x = 1;
    while (b)
    {
        T q = a / b;
        T t = b;
        b = a % b;
        a = t;
        t = xx;
        xx = x - q * xx;
        x = t;
        t = yy;
        yy = y - q * yy;
        y = t;
    }
    return a;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<T, T> CRT(T a1, T m1, T a2, T m2)
{
    T p, q;
    T g = extended_euclid(m1, m2, p, q);
    if (a1 % g != a2 % g)
        return make_pair(0, -1);
    T m = m1 / g * m2;
    p = (p % m + m) % m;
    q = (q % m + m) % m;
    return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) % m, m);
}

pair<T, T> CRT_all(const vector<T> &A, const vector<T> &M)
{
    if (A.size() != M.size())
        return {0, -1}; // invalid input

    T a = A[0], m = M[0];
    for (int i = 1; i < A.size(); i++)
    {
        auto [next_a, next_m] = CRT(a, m, A[i], M[i]);
        if (next_m == -1)
            return {0, -1}; // no solution
        a = next_a;
        m = next_m;
    }
    return {a, m}; // x ≡ a mod m
}
void print_uint128(T num)
{
    if (num == 0)
    {
        cout << "0";
        return;
    }
    string s;
    while (num > 0)
    {
        s += '0' + (num % 10);
        num /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}