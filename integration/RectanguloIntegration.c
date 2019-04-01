#include <math.h>
#include <stdio.h> 

/*La función elegida para realizar las pruebas fue la siguiente:
 * Función f(x) = 2*x
 */  
float func(float x) 
{ 
    return x*2; 
} 

/*
 * El método rectangulo o punto medio consiste en trazar un número finito de rectángulos 
 * dentro de un área irregular,calcular el área de cada uno de ellos y sumarlos. El problema de este método
 * de integración numérica es que al sumar las áreas se obtiene un margen de error muy grande.*/

float rectangleMethod(float ll, float ul, int n) 
{ 
      int j;
      float a,b,h,h2, aij, sumatoria;
		
	  a = 0;     
      b = 2.;
      h = (b-a)/n;
      sumatoria = 0.0;                 
      h2 = h/2.;
      for (j=0;j<n;j++) {             
        aij = a + j*h;
        sumatoria += func(aij+h2)*h;
      }
      return sumatoria;
} 
  
int main() 
{ 
    float limite_inferior = 0; 
    float limite_superior = 2;  
    int n = 6;  
    
    printf("Valor por método Rectangulo  %f",rectangleMethod(limite_inferior, limite_superior, n)); 
    return 0; 
} 
