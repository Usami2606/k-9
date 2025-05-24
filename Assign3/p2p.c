#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int size;
    double start, all_time;
    int rank, nprocs, i;
    double *sendbuf, *recvbuf, *send_resbuf, *recv_resbuf;  // Change the array type to double
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    //printf("my rank is %d and size is %d\n", rank, nprocs);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    //printf("Rank %d running on %s\n", rank, hostname);

    if (argc >= 2) {
        size = atoi(argv[1]);  // Get the array size from the argument
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


    // Check that number of process is not 1
    if (nprocs < 2) {
        if (rank == 0) {
            fprintf(stderr, "This program requires at least 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int t = 100;
    sendbuf = malloc(sizeof(double) * size);  // Dynamically resize
    recvbuf = malloc(sizeof(double) * size);

    send_resbuf = malloc(sizeof(double) * 1);
    recv_resbuf = malloc(sizeof(double) * 1);

    memset(sendbuf, 0, sizeof(double) * size);
    memset(recvbuf, 0, sizeof(double) * size);

    memset(send_resbuf, 0, sizeof(double) * 1);
    memset(recv_resbuf, 0, sizeof(double) * 1);

    // Check for malloc success
    if (sendbuf == NULL) {
        fprintf(stderr, "Memory allocation failed for size %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);  // If memory allocation fails, terminate the MPI program
    }

    if (rank == 0) {
        // Set the data to send
        for (i = 0; i < size; i++) {
            sendbuf[i] = (double)rand() / (double)RAND_MAX;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);  // Synchronization

    // 送信時間の計測
    // start = MPI_Wtime();
    // if (rank == 0) {
    //     MPI_Send(sendbuf, size, MPI_DOUBLE, 1, 2025, MPI_COMM_WORLD);
    // }

    // if (rank == 1) {
    //     MPI_Recv(recvbuf, size, MPI_DOUBLE, 0, 2025, MPI_COMM_WORLD, &status);
    // }

    for (t = 0; t < 100; t++) {
        if (t == 0) {
            start = MPI_Wtime();
        }

        if (rank == 0) {
            MPI_Send(sendbuf, size, MPI_DOUBLE, 1, t, MPI_COMM_WORLD);
            MPI_Recv(sendbuf, size, MPI_DOUBLE, 1, t, MPI_COMM_WORLD,
                &status);
        } else if (rank == 1) {
            MPI_Recv(recvbuf, size, MPI_DOUBLE, 0, t, MPI_COMM_WORLD, &status);
            MPI_Send(sendbuf, size, MPI_DOUBLE, 0, t, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    all_time = MPI_Wtime() - start; 


    // Result Display
    if (rank == 0) {
        //printf("rank0 send time: %f\n", all_time);
        send_resbuf[0] = all_time;
    } else if (myrank == 1) {
        //printf("rank1 recv time: %f\n", all_time);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        MPI_Send(send_resbuf, 1, MPI_DOUBLE, 1, 428, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(recv_resbuf, 1, MPI_DOUBLE, 0, 428, MPI_COMM_WORLD, &status);

        if (recv_resbuf[0] > all_time) {
            printf("result time: %f\n", recv_resbuf[0]);
        } else  {
            printf("result time: %f\n", all_time);
        }
    }

    // Free the buf memory
    free(sendbuf);
    free(recvbuf);
    free(send_resbuf);
    free(recv_resbuf);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
