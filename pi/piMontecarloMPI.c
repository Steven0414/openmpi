#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#define SEED 35791246
 
int main(int argc, char* argv[])
{
    long niter = 1000000;
    int worker;                     //Lleva el numero de proceso
    double x,y;                     //Valor de x y y para los rands
    int i, count=0;                 //Contador de buenas coordenadas
    double z;                       //Validador de x^2+y^2<=1
    double pi;                      //Acumula el valor aproximado de pi
    int nodenum = 1;
 
    MPI_Init(&argc, &argv);                 //Inicializacion de MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &worker);           //Se obtiene el rank
    MPI_Comm_size(MPI_COMM_WORLD, &nodenum);
    int recieved[nodenum];
    long recvniter[nodenum];
    srand(SEED+worker);                       //Asignacion de semilla para el rand
 
    if(worker != 0) {
        for (i=0; i<niter; ++i)                  //for principal
        {
            x= ((double)rand())/RAND_MAX;           //Coordenada x rand
            y =((double)rand())/RAND_MAX;           //Coordenada y rand
            z = sqrt(x*x+y*y);                  //Valida si esta en el circulo unitario
            if (z<=1) {
                count++;                //Se consdera como un punto valido
            }
        }
        for(i=0; i<nodenum; ++i) {
            MPI_Send(&count,1,MPI_INT,0,1,MPI_COMM_WORLD);
            MPI_Send(&niter,1,MPI_LONG,0,2,MPI_COMM_WORLD);
        }
    }
    else if (worker == 0) {
        for(i=0; i<nodenum; ++i) {
            MPI_Recv(&recieved[i],nodenum,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&recvniter[i],nodenum,MPI_LONG,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
    }
 
    if (worker == 0) {
        int conteo = 0;
        long finalniter = 0;
        for(i = 0; i<nodenum; ++i) {
            conteo += recieved[i];
            finalniter += recvniter[i];
        }
        pi = ((double)conteo/(double)finalniter)*4.0;               //p = 4(m/n)
        printf("Pi: %f\n", pi);             //Imprime el valor obtenido de pi
    }
    MPI_Finalize();                     //Finalizar MPI
    return 0;
}

















