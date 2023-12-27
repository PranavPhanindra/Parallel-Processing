#include<omp.h>
#include<stdio.h>

double func(int i)
{
    return i;
}

int main()
{
    int i,nthreads;
    double zz,res = 0.0;
    double start,end;

    printf("\nNo of threads: ");
    scanf("%d",&nthreads);
    omp_set_num_threads(nthreads);
    
    start = omp_get_wtime();
    //reduction(+:res) private(zz)
    #pragma omp parallel for 
    for(i=0;i<1000;i++)
    {  
        zz=func(i);
        res+=zz;
        printf("%d\t",omp_get_thread_num());
    }
    end = omp_get_wtime();
    
    
    printf("\nTime for execution %d : %f", nthreads , end - start);
    printf("\n%f",res);

    return 0;
}