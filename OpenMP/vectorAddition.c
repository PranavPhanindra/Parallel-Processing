#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double omp_get_wtime(void);

int* createRandomArray(int size) 
{
    // Declare an array of given size
    int* array = (int*)malloc(size * sizeof(int));

    if (array == NULL){printf("Memory allocation failed.\n"); return NULL;}
    
    // Seed the random number generator
    
    for (int i = 0; i < size; i++){array[i] = rand()%100;}
    
    return array;
}

void printArray(int* ary, int size)
{
    if (ary == NULL){printf("ERROR!! Unallocated\n");exit ;} 
    
    printf("[ ");
    
    for (int i = 0; i < size - 1; i++){ printf("%d, ", ary[i]);} 
    
    printf("%d ]\n", ary[size - 1]);
}

int main()
{
    int insize;
    int* ary1;
    int* ary2;
    double start_time;
    double end_time;
    
    printf("Enter the input size of vectors: ");
    scanf("%d", &insize); 

    srand(time(NULL));
    int sumArray[insize];
    
    ary1 = createRandomArray(insize);
    printf("Array 1:\t");
    printArray(ary1, insize);

    ary2 = createRandomArray(insize);
    printf("Array 2:\t");
    printArray(ary2, insize);
    
    
    start_time = omp_get_wtime();

    #pragma omp prallel for
    for(int i=0;i != insize;++i)
    {sumArray[i]=ary1[i]+ary2[i];}

    end_time = omp_get_wtime();

    printArray(sumArray,insize);
    
    // Free the allocated memory
    free(ary1);
    free(ary2);

    printf("Amount of time taken : %f\n",end_time-start_time);

    return 0;
}
