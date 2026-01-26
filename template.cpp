#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef int64_t ll;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> PBDS;
ll mx = INT64_MAX;
ll mn = INT64_MIN;

typedef __int128_t ii;
// pa imprimir
ostream &operator<<(ostream &os, const ii &value)
{
    char buffer[64];
    char *pos = end(buffer) - 1;
    *pos = '\0';
    __int128 tmp = value < 0 ? -value : value;
    do
    {
        --pos;
        *pos = tmp % 10 + '0';
        tmp /= 10;
    } while (tmp != 0);
    if (value < 0)
    {
        --pos;
        *pos = '-';
    }
    return os << pos;
}

//====================================================================
//                          MAIN
//====================================================================
void solved()
{
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << fixed;
    // freopen("bcount.in", "r", stdin);
    // freopen("bcount.out", "w", stdout);
    ll n;
    cin >> n;
    while (n--)
        solved();
}