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

      int myid;
      float my_result;

      a = 0;           /* Límite inferior */
      b = 2;     /* Límite superior */
      n = 100000;          /* Número de incremento en cada proceso */

      MPI_Init(&argc,&argv);              /* starts MPI */
      MPI_Comm_rank(MPI_COMM_WORLD, &myid);  /* get current process id */
      MPI_Comm_size(MPI_COMM_WORLD, &p);     /* get number of processes */

      h = (b-a)/n;    /* Longitud del incremento */
      num = n/p;	/* Número de intervalos calculados por cada proceso*/
      my_range = (b-a)/p; 
      my_a = a + myid*my_range;
      my_result = rectangleMethod(my_a,num,h);

            printf("El proceso %d tiene el resultado  %f\n", myid,my_result);

/* Se hace uso de MPI_Reduce para la recolección de datos */		      
      MPI_Reduce(&my_result, &result,1,MPI_REAL,MPI_SUM,0,MPI_COMM_WORLD);

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

float fct(float x)
{
      return x*2;
}
