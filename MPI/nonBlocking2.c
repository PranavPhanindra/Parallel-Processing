#include <mpi.h>
#include <stdio.h>

#define BUFFER_SIZE 2
#define REQS_LENGTH 4

int main(int argc, char *argv[]) {
    int numtasks, rank, prev, next;
    int tag1 = 1, tag2 = 2;
    int buf[BUFFER_SIZE];

    MPI_Request reqs[REQS_LENGTH]; // Requests array for handling message sending

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    prev = (rank - 1 + numtasks) % numtasks;
    next = (rank + 1) % numtasks;

    // Initialize the buffers
    buf[0] = rank;
    buf[1] = rank;

    // Post non-blocking receive operations for messages from previous and next neighbors
    MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
    MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);

    // Post non-blocking send operations to send messages to previous and next neighbors
    MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[2]);
    MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[3]);

    printf("Process %d sending message to %d and %d\n", rank, prev, next);

    // Wait for the completion of all non-blocking communication operations
    MPI_Waitall(REQS_LENGTH, reqs, MPI_STATUSES_IGNORE);

    MPI_Finalize();
    return 0;
}
