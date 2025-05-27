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

    int *sendbuf = malloc(sizeof(int) * length);
    int *recvbuf = malloc(sizeof(int) * length);

    int t;

    for (t = 0; t < length; t++) {
        sendbuf[t] = 0;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();
    MPI_Status status;

    if (rank == 0) {
        // printf("rank0: sending...\n");
        // fflush(stdout);
        MPI_Send(sendbuf, length, MPI_INT, 1, 317, MPI_COMM_WORLD);
        // printf("rank0: sent.\n");
        // fflush(stdout);
    } else if (rank == 1) {
        // printf("rank1: receiving...\n");
        // fflush(stdout);
        MPI_Recv(recvbuf, length, MPI_INT, 0, 317, MPI_COMM_WORLD, &status);
        // printf("rank1: received.\n");
        // fflush(stdout);
        // printf("RE %f\n", MPI_Wtime() - start);
        // fflush(stdout);
    }


    MPI_Barrier(MPI_COMM_WORLD);
    double meas_time = MPI_Wtime() - start;
    // printf("rank%d meas_time : %f\n", rank, meas_time);
    // fflush(stdout);

    if (rank == 0) {
        MPI_Send(&meas_time, 1, MPI_DOUBLE, 1, 428, MPI_COMM_WORLD);
    } else if (rank == 1) {
        double other_time;
        MPI_Recv(&other_time, 1, MPI_DOUBLE, 0, 428, MPI_COMM_WORLD, &status);
        double res_time = (other_time > meas_time) ? other_time : meas_time;
        printf("%f\n", res_time);
    }

    free(sendbuf);
    free(recvbuf);

    MPI_Finalize();
    return 0;
}
