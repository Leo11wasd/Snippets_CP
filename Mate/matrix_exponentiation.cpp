ll MOD = 1e9 + 7;
template <typename T>
void matmul(vector<vector<T>> &a, vector<vector<T>> b)
{
    int n = a.size(), m = a[0].size(), p = b[0].size();
    assert(m == b.size());
    vector<vector<T>> c(n, vector<T>(p));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < m; k++)
            {
                c[i][j] = (c[i][j] + ((a[i][k] * b[k][j]) % MOD)) % MOD;
            }
        }
    }
    a = c;
}
template <typename T>
struct Matrix
{
    vector<vector<T>> mat;
    Matrix() {}
    Matrix(vector<vector<T>> a) { mat = a; }
    Matrix(int n, int m)
    {
        mat.resize(n);
        for (int i = 0; i < n; i++)
        {
            mat[i].resize(m);
        }
    }
    int rows() const { return mat.size(); }
    int cols() const { return mat[0].size(); }
    // makes the identity matrix for a n by n matrix
    void makeiden()
    {
        for (int i = 0; i < rows(); i++)
        {
            mat[i][i] = 1;
        }
    }
    void print() const
    {
        for (int i = 0; i < rows(); i++)
        {
            for (int j = 0; j < cols(); j++)
            {
                cout << mat[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    Matrix operator*=(const Matrix &b)
    {
        matmul(mat, b.mat);
        return *this;
    }
    Matrix operator*(const Matrix &b) { return Matrix(*this) *= b; }
};

// Matrix<ll> cur(n, n);
//     cur.makeiden();
//     while (k > 0)
//     {
//         if (k & 1)
//         {
//             cur *= mat;
//         }
//         mat *= mat;
//         k >>= 1;
//     }