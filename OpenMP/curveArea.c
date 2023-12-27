#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;

int omp_get_num_threads(void);
void omp_set_num_threads(int num_threads);

int main()
{
    int num_threads = omp_get_num_threads();
    omp_set_num_threads(10);
    printf("No of threads : %d\n",num_threads);

    #pragma omp parallel
    {
        int i;
        double x,pi,sum = 0.0 ;
        step = 1.0/(double )num_steps;
        #pragma omp parallel for
        for(int i = 0 ; i != num_steps ; ++i)
        {
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }

    pi = step * sum;
    printf("\nValue of pi : %f\n",pi);
    }
    
    //printf("\nValue of pi : %f\n",pi);

    return 0;
}