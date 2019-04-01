#include <mpi.h>
#include <math.h>
#include <stdio.h>

float rectangleMethod(float local_a, int local_n, float h); 
float fct(float x);
int main(argc,argv)
int argc;
char *argv[];
{
      int n, p,num;
      float h, result, a, b;
      float my_a, my_range;

      int myid, source, dest, tag;
      MPI_Status status;
      float my_result;

      a = 0;           /* Límite inferior */
      b = 2;     /* Límite superior */
      n = 100000;          /* Número de incremento en cada proceso */

      dest = 0;         /* Definición del proceso que hace el computo del resultado */
      tag = 123;        /* Etiqueta para identificar una tarea particular */

/* Starts MPI processes ... */

      MPI_Init(&argc,&argv);              
      MPI_Comm_rank(MPI_COMM_WORLD, &myid);  
      MPI_Comm_size(MPI_COMM_WORLD, &p);     

      h = (b-a)/n;    /* Longitud del incremento */
      num = n/p;	/* Número de intervalos calculados por cada proceso*/
      my_range = (b-a)/p; 
      my_a = a + myid*my_range;
      my_result = rectangleMethod(my_a,num,h);

      printf("El proceso %d tiene el resultado  %f\n", myid,my_result);

      if(myid == 0) {
        result = my_result;
        for (int i=1;i<p;i++) {
          source = i;           /* El número del proceso se encuentra en el rango  [0,p-1] */
          MPI_Recv(&my_result, 1, MPI_REAL, source, tag,
                        MPI_COMM_WORLD, &status);
          result += my_result;
        }
        printf("El resultado es =%f\n",result);
      }
      else
        MPI_Send(&my_result, 1, MPI_REAL, dest, tag,
                      MPI_COMM_WORLD); 
      MPI_Finalize();                       
}

/*
 * El método rectangulo o punto medio consiste en trazar un número finito de rectángulos 
 * dentro de un área irregular,calcular el área de cada uno de ellos y sumarlos. El problema de este método
 * de integración numérica es que al sumar las áreas se obtiene un margen de error muy grande.*/
float rectangleMethod(float a, int n, float h){
	
	  int j;
      float h2, aij, sumatoria;

      sumatoria = 0.0;                 
      h2 = h/2.;
      for (j=0;j<n;j++) {             
        aij = a + j*h;        
        sumatoria += fct(aij+h2)*h;
      }
      return (sumatoria);
}

/*La función elegida para realizar las pruebas fue la siguiente:
 * Función f(x) = 2*x
 */  
float fct(float x)
{
      return x*2;
}
