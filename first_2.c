#include<stdio.h>
#include<mpi.h>


int main(int argc, char **argv) { 
    double precision = 1000000000; 
    int myrank, proccount; 
    double pi, pi_final; 
    int mine, sign, ranges;
    int i; 

    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 
    MPI_Comm_size(MPI_COMM_WORLD, &proccount); 

    if (precision<proccount) { 
    	printf("Precision smaller than the number of processes - try again."); 
    	MPI_Finalize(); 
    	return -1; 
    } 

    pi=0; 
    ranges = precision / proccount;
    mine=myrank*ranges+1; 
    sign=(((mine-1)/2)%2)?-1:1; 

    for (int i=0;i<ranges;i++) { 
    	pi+=sign/(double)mine; 
    	mine+=2; 
    	sign=(((mine-1)/2)%2)?-1:1; 
    } 

    MPI_Reduce(&pi,&pi_final,1, 
               MPI_DOUBLE,MPI_SUM,0, 
      	       MPI_COMM_WORLD); 

    if (!myrank) { 
    	pi_final*=4; 
    	printf("pi=%f\n",pi_final); 
    } 

    MPI_Finalize(); 
    return 0; 
} 
