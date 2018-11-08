//kshitizhamal
//csci475
//program2


#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <math.h>
#include "mpi.h"
#define ROW 128
#define COL 128
#define N 128

int main(int argc, char *argv[])
{
	int id, processes;
	int ArrayA[ROW][COL];
	int vectorB[N];
	char filenum1[255],filenum2[255];
	int length;
	int sendlength, recvlength;
	int sendArray, recvArray;
    FILE *filenum1, *filenum2;
	int *b;
	int *a;
	int i, j ,k,l;

	MPI_Init(&argc,&argv);
    MPI_Comm_length(MPI_COMM_WORLD,&processes);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
	
	

	printf("%d  Processors participate this computation.  Rank is %d.  \n", processes, id);
	
	

	

	 if (id == 0) /* Root Process opens input file and initialize data */
		{  
              
			  strcpy(filenum1,"vector.txt");
                if ((filepath1 = fopen(filenum1,"r")) == NULL) 
				{
                        printf("Can't open the vectorB.txt file: %s\n\n", filenum1);
                        exit(1);
                }
				printf("Reading all integer from vectorB.txt file in the root processor:\n ");
				for(i = 0; i < N; ++i)
                {
                        fscanf(filepath1,"%d", &vector[i]);
						printf("%d\n", vector[i]);
                }
                printf("\n");
				
				strcpy(filenum2,"matrix.txt");
                if ((filepath2 = fopen(filenum2,"r")) == NULL) 
				{
                        printf("Can't open the matrix.txt file: %s\n\n", filenum2);
                        exit(1);
                }
				printf("Reading all integer from matrix.txt file in the root processor:\n ");
				for(i = 0; i < ROW; ++i)
				{
						for(j = 0; j < COL; ++j)
						{
							fscanf(filepath2,"%d",&ArrayA[i][j]);
							
						}
				}
                printf("\n"); 
				
        }	
		
   int x = ROW / processes;
	int in = N /processes;
	sendlength = in;
	recvlength = sendlength;

b = (int *) malloc(N*lengthof(int));
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(vectorB,sendlength,MPI_INT,b,recvlength,MPI_INT,0,MPI_COMM_WORLD);
	
	
	printf("The Rank of the Process is: %d \n",id);
	printf("Data received from vector\n");
	
	printf("--------------- \n");

	
	for( i= 0; i < in; ++i)
	{
		printf("%d\n",b[i]);
	}
	

	length = (ROW *x)* lengthof(int);
	a = (int *)malloc(length);
	
	sendArray = ROW * x; 
	recvArray = sendArray ;
	
	
	
	MPI_Scatter(ArrayA,sendArray,MPI_INT,a,recvArray,MPI_INT,0,MPI_COMM_WORLD);
	
	int low = id * x;
	int high = ((id+1)*x)-1;
	
	

	printf("Rank of the Process is: %d \n",id);
	
	
	printf("Data received from ArrayA\n");
	printf("------------------------\n");
 
		
	for( j= low; j <= high; ++j)
	
  
	for( k = 0; k < COL; ++k)
			
			printf("Array[%d][%d]: %d\n",j,k,a[(j*8+k)%(2*N)]);

	printf("\n");
	MPI_Finalize();
 
	return 0;
}

