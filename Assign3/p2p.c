#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);

    int rank, size, length;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char *procName = malloc(sizeof(char) * 300);
	int len=0;
	MPI_Get_processor_name(procName, &len);
	//printf("%s:%d/%d\n",procName,rank,size);

    if (argc == 2) {
        length = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
    }
    //printf("%d\n", length);

    double *sendbuf = malloc(sizeof(double) * length);
    double *recvbuf = malloc(sizeof(double) * length);

    int t;

    for (t = 0; t < length; t++) {
        sendbuf[t] = 0;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Status status;
    double start = MPI_Wtime();

    for (t = 0; t < 100; t++) {
        if (rank == 0) {
            MPI_Send(sendbuf, length, MPI_DOUBLE, 1, 317, MPI_COMM_WORLD);
            MPI_Recv(recvbuf, length, MPI_DOUBLE, 1, 317, MPI_COMM_WORLD, &status);
        } else if (rank == 1) {
            MPI_Recv(recvbuf, length, MPI_DOUBLE, 0, 317, MPI_COMM_WORLD, &status);
            MPI_Send(recvbuf, length, MPI_DOUBLE, 0, 317, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double meas_time = MPI_Wtime() - start;

    if (rank == 0) {
        printf("%f\n", meas_time / 200);
    }

    // if (rank == 1) {
    //     MPI_Send(&meas_time, 1, MPI_DOUBLE, 0, 428, MPI_COMM_WORLD);
    // } else if (rank == 0) {
    //     double other_time;
    //     MPI_Recv(&other_time, 1, MPI_DOUBLE, 1, 428, MPI_COMM_WORLD, &status);
    //     double res_time = (other_time > meas_time) ? other_time : meas_time;
    //     printf("%f\n", res_time);
    // }

    free(sendbuf);
    free(recvbuf);

    MPI_Finalize();
    return 0;
}
