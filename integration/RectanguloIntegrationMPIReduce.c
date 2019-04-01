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
      my_result = simpson(my_a,num,h);

            printf("El proceso %d tiene el resultado  %f\n", myid,my_result);

/* Se hace uso de MPI_Reduce para la recolección de datos */		      
      MPI_Reduce(&my_result, &result,1,MPI_REAL,MPI_SUM,0,MPI_COMM_WORLD);

      MPI_Finalize();
}

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

float fct(float x)
{
      return x*2;
}
