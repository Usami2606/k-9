#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // gethostname()
#include <mpi.h>

int main(int argc, char* argv[])
{
        int myrank, nprocs;
        char hostname[64]; 

        MPI_Init(&argc, &argv);

        //ホスト名を取得
        gethostname(hostname, 64);
        //rank番号の取得
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        //起動プロセス数の取得
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        //
        printf("[%d/%d] my host name is %s!!!\n", myrank, nprocs, hostname);


        MPI_Finalize();
        return 0;
}