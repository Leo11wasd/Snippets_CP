// La idea es probar en cada posición del número a rellenar que dígitos podemos colocar. 
// Si en una posición de previa (que valen más) ya asegure que el número que estamos creando 
// es menor que el límite a, entonces en esta posición se puede colocar cualquier dígito, 
// caso contrario, el dígito no puede ser mayor que el dígito de a en esta posición

// Código de ejemplo básico para calcular cuántos números entre 0 y a cumplen que la suma de sus dígitos es d

// dp[cantidad_de_digitos][suma%d][bool_enrango]
ll dp[10005][100][2];
/*regresa cuantos números entre 0 y a cumplen que
la suma de sus digitos es d
*/
ll func(string &a, int d)
{
   ll ni, nj, nk, limite;
   ll n = a.size();
   dp[0][0][0] = 1;
   // para todo digito en el número
   for (int i = 0; i < n; i++)
   {
       ni = i + 1;
       // probemos poner el dígito
       for (int j = 0; j < d; j++)
       {
           for (int k = 0; k < 2; k++)
           {
               if (k == 1)
               {
                   limite = 9;
               }
               else
               {
                   limite = a[i] - '0';
               }
               for (int digito = 0; digito <= limite; digito++)
               {
                   // suma modulo d
                   nj = suma(j, digito, d);
                   if (k == 1 || digito < limite)
                   {
                       nk = 1;
                   }
                   else
                   {
                       nk = 0;
                   }
                   // cout<<nj<<" aumenta en "<<dp[i][j][k]<<" al agregar "<<digito<<endl;
                   // suma modulo mod(1e9+7 por ejemplo)
                   dp[ni][nj][nk] = suma(dp[ni][nj][nk], dp[i][j][k], mod);
               }
           }
       }
   }
   // suma modulo mod(1e9+7 por ejemplo)
   return suma(dp[n][0][0], dp[n][0][1], mod);
}
