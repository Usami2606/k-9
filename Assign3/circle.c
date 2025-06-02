#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    int rank, size, length;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //printf("my rank is %d and size is %d\n", rank, nprocs);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    //printf("Rank %d running on %s\n", rank, hostname);

    if (argc == 2) {
        length = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
    }

    double *sendbuf = malloc(sizeof(double) * length); 
    double *recvbuf = malloc(sizeof(double) * length);

    int t = 0;
    for (t = 0; t < length; t++) {
        sendbuf[t] = (double)rank;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    int to_rank = (rank + 1) % size;
    int from_rank = (size + rank - 1) % size;
	MPI_Status status;
	MPI_Request request, rep_request;
    MPI_Isend(sendbuf, length, MPI_DOUBLE, to_rank, 317, MPI_COMM_WORLD, &request);
	MPI_Recv(recvbuf, length, MPI_DOUBLE, from_rank, 317, MPI_COMM_WORLD, &status);
	MPI_Wait(&request, &status);

    MPI_Isend(sendbuf, length, MPI_DOUBLE, from_rank, 428, MPI_COMM_WORLD, &rep_request);
	MPI_Recv(recvbuf, length, MPI_DOUBLE, to_rank, 428, MPI_COMM_WORLD, &status);
	MPI_Wait(&rep_request, &status);

    MPI_Barrier(MPI_COMM_WORLD);

    double res_time = (MPI_Wtime() - start) / 2;
    double max_time;

    MPI_Reduce(&res_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("%lf\n", max_time);
        //printf("%d\n", recvbuf[1]);
    }

    free(sendbuf);
    free(recvbuf);

    MPI_Finalize();

    return 0;

}

