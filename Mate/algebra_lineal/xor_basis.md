# Xor basis

## Complexity

- Time:
- Memory:

## Notes

- Nos permite obtener una base de entre un conjunto de vectores cuyas entradas son únicamente valores 0 o 1.

- Se utiliza en problemas en los que nos dan un conjunto de números y se nos pide encontrar una respuesta que involucra a todas las posibles sumas xor que se pueden obtener a partir de todos los posibles subconjuntos del arreglo.

- base[i]= un número del arreglo que tiene como bit menos significativo en 1 al bit i.
Por cómo formamos la base, este número es único dentro de la base. Es decir, no hay otro número en la base con bit menos significativo en 1 igual al bit i.

- Si queremos definir a base[i] como el número de la base con el bit más significativo en 1 igual al bit i,
entonces basta con invertir el for dentro de insertVector para que vaya de LOG_A-1 a 0

- El codigo de insertVector verifica si el vector que se ingresa es una combinación lineal de los vectores que hasta ahora forman parte de la base. Solamente si no es combinación lineal lo agrega. 

## Code

```cpp
ll LOG_A;
vector<ll> base; // base generada 

ll sz_base; // tamaño de la base

void insertVector(ll mask)
{
    for (int i = 0; i < LOG_A; i++)
    {
        if ((mask & (1ll << i)) == 0)
            continue;

        if (base[i] == 0)
        {
            base[i] = mask;
            ++sz_base;

            return;
        }

        mask ^= base[i];
    }
}
// LOG_A = k; //para numeros entre 0 y (2^k)-1
// base.assign(LOG_A, 0);
```