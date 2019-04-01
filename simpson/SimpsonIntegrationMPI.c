#include <mpi.h>
#include <math.h>
#include <stdio.h>

float simpson(float local_a, int local_n, float h); 
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
      my_result = simpson(my_a,num,h);

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

/*El Método de Simpson sustituye a la curva  por una serie de arcos contiguos, 
cada uno de estos arcos es un arco de parábola de eje vertical. Esto nos 
lleva a aproximar el área bajo la curva mediante la suma de las áreas bajo cada arco de parábola*/
float simpson(float local_a, int local_n, float h){
	
	float result = 0;
	for(int i =0; i<=local_n; i++)
	{
		if((i==0)||(i==local_n))
			result += fct(local_a + i* h);
		else if(i%2==0)
			result += 2* fct(local_a + i*h);
		else
			result += 4* fct(local_a + i*h);	
	}
	result *= h/3;  
	return(result);
}

/*La función elegida para realizar las pruebas fue la siguiente:
 * Función f(x) = 2*x
 */  
float fct(float x)
{
      return x*2;
}
