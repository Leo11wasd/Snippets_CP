ll maximo = 1e5 + 5;
bitset<1000005> noprimo;

void criba()
{
    //el 1 no es primo xd
    noprimo[0] = noprimo[1] = 1;
    for (int i = 4; i < maximo; i += 2)
        noprimo[i] = 1;
    for (int i = 3; i < maximo; i += 2)
    {
        if (!noprimo[i])
        {
            for (int j = i + i; j < maximo; j += i)
            {
                noprimo[j] = 1;
            }
        }
    }
}