#include<stdio.h>
#include<mpi.h>


int main(int argc, char **argv) { 
    double precision=1000000000; 
    int myrank,proccount; 
    double pi,pi_final; 
    int mine,sign, first, second; 
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
    first = 4 * myrank + 1;
    second = first + 2;

    for (;first<precision;) { 
    	pi+=(1/(double)first ) - (1/(double)second);
    	first+=4*proccount;
        second = first + 2;
    } 

    MPI_Reduce(&pi,&pi_final,1, 
               MPI_DOUBLE,MPI_SUM,0, 
      	       MPI_COMM_WORLD); 

    if (!myrank) { 
    	pi_final*=4; 
    	printf("pi=%f",pi_final); 
    } 

    MPI_Finalize(); 
    return 0; 
}
