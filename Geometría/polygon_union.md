# Polygon Union

## Complexity

- Time:
- Memory:

## Notes

-

## Code

```cpp
const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double)-1.0);
int sign(double x) { return (x > eps) - (x < -eps); }

struct PT
{
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator+(const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator-(const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator*(const double a) const { return PT(x * a, y * a); }
    friend PT operator*(const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator/(const double a) const { return PT(x / a, y / a); }
    bool operator==(PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator!=(PT a) const { return !(*this == a); }
    bool operator<(PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator>(PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    double norm() { return sqrt(x * x + y * y); }
    double norm2() { return x * x + y * y; }
    PT perp() { return PT(-y, x); }
    double arg() { return atan2(y, x); }
    PT truncate(double r)
    { // returns a vector with norm r and having same direction
        double k = norm();
        if (!sign(k))
            return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
// cross > 0 ccw, cross < 0 cw
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }


double rat(PT a, PT b, PT p)
{
    return !sign(a.x - b.x) ? (p.y - a.y) / (b.y - a.y) : (p.x - a.x) / (b.x - a.x);
};
double polygon_union(vector<vector<PT>> &p)
{
    int n = p.size();
    double ans = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int v = 0; v < (int)p[i].size(); ++v)
        {
            PT a = p[i][v], b = p[i][(v + 1) % p[i].size()];
            vector<pair<double, int>> segs;
            segs.emplace_back(0, 0), segs.emplace_back(1, 0);
            for (int j = 0; j < n; ++j)
            {
                if (i != j)
                {
                    for (size_t u = 0; u < p[j].size(); ++u)
                    {
                        PT c = p[j][u], d = p[j][(u + 1) % p[j].size()];
                        int sc = sign(cross(b - a, c - a)), sd = sign(cross(b - a, d - a));
                        if (!sc && !sd)
                        {
                            if (sign(dot(b - a, d - c)) > 0 && i > j)
                            {
                                segs.emplace_back(rat(a, b, c), 1), segs.emplace_back(rat(a, b, d), -1);
                            }
                        }
                        else
                        {
                            double sa = cross(d - c, a - c), sb = cross(d - c, b - c);
                            if (sc >= 0 && sd < 0)
                                segs.emplace_back(sa / (sa - sb), 1);
                            else if (sc < 0 && sd >= 0)
                                segs.emplace_back(sa / (sa - sb), -1);
                        }
                    }
                }
            }
            sort(segs.begin(), segs.end());
            double pre = min(max(segs[0].first, 0.0), 1.0), now, sum = 0;
            int cnt = segs[0].second;
            for (int j = 1; j < segs.size(); ++j)
            {
                now = min(max(segs[j].first, 0.0), 1.0);
                if (!cnt)
                    sum += now - pre;
                cnt += segs[j].second;
                pre = now;
            }
            ans += cross(a, b) * sum;
        }
    }
    return ans * 0.5;
}
```