#include <stdlib.h>                                         
#include <time.h>                                           
#include <stdio.h>

double  getPiMetodoMC() {
	int INTERVAL = 10000;
	double rand_x,rand_y,origin_dist,pi;
    int circle_points=0,square_points=0;

    srand(time(NULL));                                      

    for(int i=0; i<(INTERVAL*INTERVAL); i++)                   
    {

        rand_x = (double)(rand()%(INTERVAL+1))/INTERVAL;      
        rand_y = (double)(rand()%(INTERVAL+1))/INTERVAL;      
		origin_dist = (double)(rand_x*rand_x + rand_y*rand_y);        

        if(origin_dist <= 1) 
        circle_points++;              
        
        square_points++;                                    

        pi = (double)(4*circle_points/square_points);         

        if(i<20){ 
			return pi; 
		}                       
    }
    return 0.0;
}

int main(int argc, char *argv[])
{    
	printf("Mi valor de pi es %f ",getPiMetodoMC());
}
