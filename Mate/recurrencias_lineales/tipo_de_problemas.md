## Exponenciación de matrices

El código de matrix_exponentiation permite elevar una matriz cuadrada de kxk en tiempo \(O(k^3 log n)\).

En el contexto de la programación competitiva, es útil para:
- Calcular recurrencias lineales.
    - Creamos una matriz A tal que A*v(i) = v(i+1), donde v(i) es un vector que contiene f(i), f(i-1), f(i-2)...f(i-k) si nuestra recurrencia depende de los k valores anteriores. La matriz A contendra en las posiciones pertinentes los coeficientes por los que hay que multiplicar para obtener el vector v(i+1)
    
- Contar caminos o calcular probabilidades sobre grafos.
    - Elevar la matriz de adyacencia a la potencia n nos deja con una matriz donde la entrada i,j tiene la cantidad de caminos que inician en i, terminan en j y pasan por n aristas. Cuando los valores en las aristas representan probabilidad de moverse de un nodo a otro, la entrada i,j de la matriz elevada a la n tiene la probabilidad de que un camino de longitud n inicie en i y termine en j.

- Calcular el camino más corto que pasa por k aristas en un grafo ponderado.
    - Se modifica la operación de multiplicación por c[i][j] = min(c[i][j], a[i][k] + b[k][j]);

