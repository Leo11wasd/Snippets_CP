# Matrix exponentiation

## Complexity

- Time: $O(k^3 log n)$
- Memory:

## Notes

En el contexto de la programación competitiva, es útil para:
- Calcular recurrencias lineales.
    - Creamos una matriz A tal que A*v(i) = v(i+1), donde v(i) es un vector que contiene f(i), f(i-1), f(i-2)...f(i-k) si nuestra recurrencia depende de los k valores anteriores. La matriz A contendra en las posiciones pertinentes los coeficientes por los que hay que multiplicar para obtener el vector v(i+1)
    
- Contar caminos o calcular probabilidades sobre grafos.
    - Elevar la matriz de adyacencia a la potencia n nos deja con una matriz donde la entrada i,j tiene la cantidad de caminos que inician en i, terminan en j y pasan por n aristas. Cuando los valores en las aristas representan probabilidad de moverse de un nodo a otro, la entrada i,j de la matriz elevada a la n tiene la probabilidad de que un camino de longitud n inicie en i y termine en j.

- Calcular el camino más corto que pasa por k aristas en un grafo ponderado.
    - Se modifica la operación de multiplicación por c[i][j] = min(c[i][j], a[i][k] + b[k][j]);



## Code

```cpp
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
```