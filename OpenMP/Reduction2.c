#include<omp.h>
#include<stdio.h>
double func(int i)
{
    return i;
}
int main()
{
    int i;
    double ZZ,res = 0.0;
    double start,end;
    int threadCount = 8;
    omp_set_num_threads(threadCount);
    start = omp_get_wtime();
    //reduction(+:res) private(ZZ)
    #pragma omp parallel for 
        for(i=0;i<1000;i++)
    {  
        ZZ=func(i);
        res+=ZZ;
        printf("%d\t",omp_get_thread_num());
    }
    end = omp_get_wtime();
    printf("Time for execution %d : %f",threadCount, end - start);
    printf("\n%f",res);
}