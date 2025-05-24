#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int size;
    double send;
    int rank, nprocs;
    double *recvbuf;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    // print("my rank is %d and size is %d\n", rank, nprocs);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    // printf("Rank %d runnning on %s\n", rank, hostname);

    if (argc >= 2) {
        size = atoi(argv[1]);
        if (size <= 0) {
            if (rank == 0) {
                fprintf(stderr, "Invalid size specified: %s\n", argv[1]);
            }
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    } else {
        if (rank == 0) {
            fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (nprocs < 2) {
        if (rank == 0)  {
            fprintf(stderr, "This program requires at least 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    recvbuf = malloc(sizeof(double) * nprocs);

    // check malloc success
    if (recvbuf == NULL) {
        fprintf(stderr, "Memory allocation failed for size %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    memset(recvbuf, 0, sizeof(double) * nprocs);

    send = (double)rank;

    MPI_Barrier(MPI_COMM_WORLD);
    printf("send : %f \n", send);
    MPI_Allgather(&send, 1, MPI_DOUBLE, recvbuf, 1, MPI_DOUBLE, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Process %d received: ", rank);
    int i;
    for (i = 0; i < nprocs; i++) {
        printf("%d ", (int)recvbuf[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}