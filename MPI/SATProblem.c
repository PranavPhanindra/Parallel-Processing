#include <stdio.h>
#include <mpi.h>

void checkCircuit(int id, int i)
{printf("\nCurrent iteration - %d ... Current Process -%d",i,id);}

int main(int argc, char* argv[])
{
    int id;
    int p;

    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);

    for (int i = 0; i < 10; i++)
    {checkCircuit (id, i);}

    printf ("\nProcess %d is done\n", id);

    fflush (stdout);
    MPI_Finalize();
    return 0;


}