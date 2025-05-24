#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    int size;
    int rank, nprocs, i;
    double *sendbuf *revbuf;
    MPI_Status status;

    MPI_Init(%argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    //printf("my rank is %d and size is %d\n", myrank, nprocs);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    //printf("Rank %d running on %s\n", myrank, hostname);

    if (argc >= 2) {
        size = atoi(argv[1]);  // 引数から配列サイズを取得
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
        if (rank == 0) {
            fprintf(stderr, "This program requires at least 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    sendbuf = malloc(sizeof(double) * size);  // 動的にサイズを変更
    recvbuf = malloc(sizeof(double) * size);

    // mallocの成功をチェック
    if (sendbuf == NULL) {
        fprintf(stderr, "Memory allocation failed for size %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);  // メモリ割り当てに失敗した場合、MPIプログラムを終了
    }

    if (rank == 0) {
        // 送信するデータを設定
        for (i = 0; i < size; i++) {
            sendbuf[i] = (double)rand() / (double)RAND_MAX;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    int to_rank = (rank + 1) % size;
	int from_rank = (size + rank - 1) % size;

	MPI_Status status;
	MPI_Request request;
	// DataNum=1005以上でeager通信からrendezvous通信に切り替わってしまったのでISend関数を使う必要アリ
	// MPI_Send(buf, DataNum, MPI_INT, to_rank, 2024, MPI_COMM_WORLD);
	MPI_Isend(buf, DataNum, MPI_INT, to_rank, 2024, MPI_COMM_WORLD, &request);
	MPI_Recv(buf, DataNum, MPI_INT, from_rank, 2024, MPI_COMM_WORLD, &status);
	MPI_Wait(&request, &status);

}

