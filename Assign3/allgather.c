#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
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
    //printf("%"d\n", length);

    double *sendbuf = malloc(sizeof(double) * length);
    double *recvbuf = malloc(sizeof(double) * length * size);

    int t;

    for (t = 0; t < length; t++) {
        sendbuf[t] = rank * 100 + t;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    MPI_Allgather(sendbuf, length, MPI_DOUBLE, recvbuf, length, MPI_DOUBLE, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double res_time = MPI_Wtime() - start;
    double max_time;

    MPI_Reduce(&res_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    //printf("rank%d : result %f\n", rank, res_time);

    if (rank == 0) {
        // int r;
        // for (r = 0; r < size; r++) {
        //     printf("Data from rank %d: ", r);
        //     int i;
        //     for (i = 0; i < 5; i++) { // 先頭5個だけ表示
        //         printf("%d ", recvbuf[r * length + i]);
        //     }
        //     printf("...\n");
        // }
        printf("%f\n", max_time);
    }

    free(sendbuf);
    free(recvbuf);

    MPI_Finalize();
    return 0;

}