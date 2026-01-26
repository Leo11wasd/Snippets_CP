# GRUNDY NUMBER

El *grundy number* es la asignación de un valor numérico a los estados de un juego tipo **Nim** que anteriormente eran victoria o derrota.  
El *grundy number* de un estado es **0** si el estado es de derrota para el jugador cuyo turno cae en ese estado y el *grundy number* es positivo si el estado es de victoria.

Entonces, definimos al *grundy number* del estado $u$ de un juego tipo Nim **de una sola pila** $G(u)$ como:

$$
G(\text{estado\_derrota}) = 0
$$

$$
G(\text{estado\_victoria}) = \operatorname{mex}(G(u)) \quad \text{para todo estado } u \text{ alcanzable desde estado\_victoria}.
$$

Si se tienen $n$ pilas, cada una con tamaño $t_i$, entonces el *grundy number* del juego en conjunto es el **xor** de los $G(t_i)$ de todas las pilas.

$$
G = G(t_1) \oplus G(t_2) \oplus \cdots \oplus G(t_n)
$$
