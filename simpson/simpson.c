#include <math.h>
#include <stdio.h> 

/*La función elegida para realizar las pruebas fue la siguiente:
 * Función f(x) = 2*x
 */  
float func(float x) 
{ 
    return x*2; 
} 

/*El Método de Simpson sustituye a la curva  por una serie de arcos contiguos, 
cada uno de estos arcos es un arco de parábola de eje vertical. Esto nos 
lleva a aproximar el área bajo la curva mediante la suma de las áreas bajo cada arco de parábola*/
float simpson(float ll, float ul, int n) 
{ 
  
    float h = (ul - ll) / n; 
    float x[10], fx[10]; 
  
    for (int i = 0; i <= n; i++) { 
        x[i] = ll + i * h; 
        fx[i] = func(x[i]); 
    } 
  
    float res = 0; 
    for (int i = 0; i <= n; i++) { 
        if (i == 0 || i == n) 
            res += fx[i]; 
        else if (i % 2 != 0) 
            res += 4 * fx[i]; 
        else
            res += 2 * fx[i]; 
    } 
    res = res * (h / 3); 
    return res; 
} 
  
int main() 
{ 
    float limite_inferior = 0; 
    float limite_superior = 2;  
    int n = 6; // Number of interval 
    printf("Valor por método Simpson  %f",simpson(limite_inferior, limite_superior, n)); 
    return 0; 
} 
