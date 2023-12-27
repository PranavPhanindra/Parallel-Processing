#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **matrixAllocator(int row,int col)
{
    //printf("\nAt MAtrix Allocator\n");
    int** matrix = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++)
    {
        //printf("\nHere\n");
        matrix[i] = (int*)malloc(col * sizeof(int));
    }

    if (matrix == NULL)
    {printf("Memory allocation failed.\n"); return NULL;}

    return matrix;
}

int **createRandomMatrix(int row,int col)
{
    //printf("\nAt Random Matrix\n");
    int** matrix = matrixAllocator(row,col);

    for(int i = 0 ; i < row ; ++i)
    {
        for(int j = 0 ; j!=col ; ++j)
        {
            matrix[i][j] = rand()%100;
        }
    }

return matrix;
}

void printMatrix(int** matrix, int rows, int columns)
{
    printf("\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freeMatrix(int **matrix , int row , int col)
{
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{
    srand(time(NULL));
    int row,col,nthreads;
    double start_time,end_time;
//-------------------------------------------------------------------------------------------------------------------------------------
    printf("Enter Dimesions of the matrices...");
    printf("\nRow : ");
    scanf("%d",&row);
    printf("\nCol: ");
    scanf("%d",&col);
    printf("\nNo of threads: ");
    scanf("%d",&nthreads);

    int **mat1 = createRandomMatrix(row,col);
    printf("Matrix -1\n");
    //printMatrix(mat1,row,col);

    int **mat2 = createRandomMatrix(row,col);
    printf("Matrix -2\n");
    //printMatrix(mat2,row,col);

    int numPrcs = omp_get_num_procs();
    printf("\nNo of prcs : %d\n",numPrcs);
//-------------------------------------------------------------------------------------------------------------------------------------
    int** sumMatrix = matrixAllocator(row,col);

    printf("No of threads created : %d\n",omp_get_num_threads());
    
    start_time = omp_get_wtime();
    omp_set_num_threads(nthreads);
    #pragma omp prallel for
    {
        for(int i=0;i < row;i++)
        {
            omp_set_num_threads(nthreads);
            #pragma omp prallel for
            for(int j = 0 ; j < col ; j++)
            {
                sumMatrix[i][j]=mat1[i][j]+mat2[i][j];
                printf(" %d",omp_get_thread_num());
                
            }
            
        }
    }
    end_time = omp_get_wtime();

    //printMatrix(sumMatrix,row,col);
    printf("\nAmount of time taken : %f\n",end_time-start_time);
//-------------------------------------------------------------------------------------------------------------------------------------
    freeMatrix(mat1,row,col);
    freeMatrix(mat2,row,col);
    freeMatrix(sumMatrix,row,col);
//-------------------------------------------------------------------------------------------------------------------------------------
    return 0;
}