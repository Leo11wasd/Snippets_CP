# TEOREMA DE DILWORTH

**Poset**: conjunto parcialmente ordenado. Un conjunto de elementos y un operador < que compara a dos elementos. No todos los elementos son comparables entre sí. (están relacionados)

**Cadena**: Secuencia donde todos los elementos son comparables (por ejemplo una secuencia estrictamente creciente)

**Anticadena**: Secuencia donde ningún par de elementos es comparable 

**Teorema de dilworth**: Sea P un poset, entonces el tamaño de una anticadena máxima= mínimo número de cadenas necesarias para cubrir a todo el poset.

Dadas parejas (ai,bi) cuál es el mínimo número de secuencias crecientes (en a y b a la vez) que cubran todas las secuencias.

1. Ordena los pares por ai ascendente y por bi ascendente.


2. Aplica Longest Decreasing Subsequence sobre los bi (o LIS con signos negados).


3. El resultado es el mínimo número de cadenas crecientes por Dilworth.
