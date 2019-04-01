#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <time.h>                                           

int main(int argc, char* argv[])
{
    int niter = 100000;
    int myid;                       //Guarda el rank del proceso
    double x,y;                     //Valores x y y para los rands
    int i;
        int count=0;                //Acumulador de coordenadas utiles
    double z;                       //Validador de x^2+y^2<=1
    double pi;                      //Acumulador de pi
    int reducedcount;                   //Numero total de soluciones
    int reducedniter;                   //Numero total de valores generados
 
    MPI_Init(&argc, &argv);                 //Inicializacion MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           //Obtiene el rank del proceso
 
 
    for (i=0; i<niter; ++i) {                 //main loop
        srand(time(NULL)+myid);               //Asignacion de la semilla 
        x = (double)random()/RAND_MAX;          //Coordenada x aleatoria
        y = (double)random()/RAND_MAX;          //Coordenada y aleatoria
        z = sqrt((x*x)+(y*y));              //Valida si el punto està en el circulo unitario
        if (z<=1) {
            ++count;                //Si lo esta lo considera como punto valido
        }
    }
     
 
    MPI_Reduce(&count,
                   &reducedcount,
                   1,
                   MPI_INT,
                   MPI_SUM,
                   0,
                   MPI_COMM_WORLD);
    MPI_Reduce(&niter,
                   &reducedniter,
                   1,
                   MPI_INT,
                   MPI_SUM,
                   0,
                   MPI_COMM_WORLD);
     
    if (myid == 0) {
        pi = ((double)reducedcount/(double)reducedniter)*4.0;               //p = 4(m/n)
        printf("Pi: %f\n%i\n%d\n", pi, reducedcount, reducedniter);
    }
 
    MPI_Finalize();                     //Finaliza mpi
    return 0;
}
