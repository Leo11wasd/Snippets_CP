## Floyd-Warshall

El código de Floyd_Warshall.cpp nos permite obtener el peso del camino más corto en un grafo dirigido en O(v^3).

La idea es resolver de manera progresiva el problema. En el paso k el arreglo respuesta d[i][j] contendrá la distancia más corta del nodo i al nodo j pasando únicamente por nodos con indice <=k (sin considerar los extremos). Inmediatamente antes del paso k, d[i][j] contiene la distancia más corta entre i y j únicamente considerando nodos intermedios entre 1 y k-1. Podemos decir que en el momento k, algunos caminos se mantendran y por tanto dp[i][j] no cambia, mientras que otros pasan por el nuevo nodo intermedio k y luego siguen hacia su destino desde ahi pasando por nodos todos distintos de k (y por tanto ya considerados en el valor actual de d[i][j]). Entonces d[i][j]=min(d[i][j],d[i][k]+d[k][j])



Tambien se puede utilizar el mismo código para recuperar el camino más corto de cualquier pareja de nodos.
Creemos el arreglo prev[i][j] que se modifica con k cada que d[i][j]>d[i][k]+d[k][j] (cuando efectivamente el camino más corto pasa por k) durante el proceso de construcción de d. Entonces, sabemos que en el camino más corto de i->j, iniciamos en i, terminamos en j y en el medio pasamos por p[i][j]=k. Luego, podemos resolver recursivamente el mismo problema para el camino más corto de i->k y el de k->j y luego incorporar esas respuestas en la del camino general.