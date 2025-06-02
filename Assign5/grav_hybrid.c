#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>
#include <sys/stat.h>
#include "grav_data/data_util_bin.c"

double second() {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    return (double)(tm.tv_sec) + (double)(tm.tv_usec) / 1.0e6;
}

int main(int argc, char** argv) {
    int np = 1000;
    int STEP = 10;
    double dt = 1.0;
    double G = 1.0;

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    //printf("Rank %d running on %s\n", rank, hostname);

    int local_np = (np + size - 1) / size;

    // Global Data
    double *m = malloc(sizeof(double) * np);
    double *prev_x = malloc(sizeof(double) * np);
    double *prev_y = malloc(sizeof(double) * np);
    double *prev_z = malloc(sizeof(double) * np);

    // Local Data
    double *local_next_x = malloc(sizeof(double) * local_np);
    double *local_next_y = malloc(sizeof(double) * local_np);
    double *local_next_z = malloc(sizeof(double) * local_np);
    double *local_prev_vx = malloc(sizeof(double) * local_np);
    double *local_prev_vy = malloc(sizeof(double) * local_np);
    double *local_prev_vz = malloc(sizeof(double) * local_np);
    double *local_prev_x = malloc(sizeof(double) * local_np);
    double *local_prev_y = malloc(sizeof(double) * local_np);
    double *local_prev_z = malloc(sizeof(double) * local_np);

    double *vx = NULL, *vy = NULL, *vz = NULL;

    double start = MPI_Wtime();

    if (rank == 0) {
        vx = malloc(sizeof(double) * np);
        vy = malloc(sizeof(double) * np);
        vz = malloc(sizeof(double) * np);

        read_data("grav_data/n1000/m.double", m, np);
        read_data("grav_data/n1000/x.double", prev_x, np);
        read_data("grav_data/n1000/y.double", prev_y, np);
        read_data("grav_data/n1000/z.double", prev_z, np);
        read_data("grav_data/n1000/vx.double", vx, np);
        read_data("grav_data/n1000/vy.double", vy, np);
        read_data("grav_data/n1000/vz.double", vz, np);
    }

    MPI_Bcast(m, np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(prev_x, np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(prev_y, np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(prev_z, np, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Scatter(prev_x, local_np, MPI_DOUBLE, local_prev_x, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(prev_y, local_np, MPI_DOUBLE, local_prev_y, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(prev_z, local_np, MPI_DOUBLE, local_prev_z, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(vx, local_np, MPI_DOUBLE, local_prev_vx, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(vy, local_np, MPI_DOUBLE, local_prev_vy, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(vz, local_np, MPI_DOUBLE, local_prev_vz, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        free(vx); free(vy); free(vz);
    }

    int t = 0;
    for (t = 0; t < STEP; t++) {
        int i = 0;
    #pragma omp parallel for
        for (i = 0; i < local_np; i++) {
            int global_i = rank * local_np + i;
            if (global_i >= np) continue; // Prevent out-of-bounds access

            double x = local_prev_x[i];
            double y = local_prev_y[i];
            double z = local_prev_z[i];

            double vx = 0.0, vy = 0.0, vz = 0.0;
            int j = 0;
            for (j = 0; j < np; j++) {
                if (j == global_i) continue;
                double dx = prev_x[j] - x;
                double dy = prev_y[j] - y;
                double dz = prev_z[j] - z;
                double r = sqrt(dx * dx + dy * dy + dz * dz);
                double r3 = r * r * r + 1e-15;

                vx += G * m[j] * dx / r3;
                vy += G * m[j] * dy / r3;
                vz += G * m[j] * dz / r3;
            }

            vx = local_prev_vx[i] + vx * dt;
            vy = local_prev_vy[i] + vy * dt;
            vz = local_prev_vz[i] + vz * dt;

            local_next_x[i] = x + vx * dt;
            local_next_y[i] = y + vy * dt;
            local_next_z[i] = z + vz * dt;

            local_prev_vx[i] = vx;
            local_prev_vy[i] = vy;
            local_prev_vz[i] = vz;
        }

        MPI_Gather(local_next_x, local_np, MPI_DOUBLE, prev_x, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(local_next_y, local_np, MPI_DOUBLE, prev_y, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(local_next_z, local_np, MPI_DOUBLE, prev_z, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        MPI_Bcast(prev_x, np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(prev_y, np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(prev_z, np, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        MPI_Scatter(prev_x, local_np, MPI_DOUBLE, local_prev_x, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(prev_y, local_np, MPI_DOUBLE, local_prev_y, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(prev_z, local_np, MPI_DOUBLE, local_prev_z, local_np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    double time = MPI_Wtime() - start;

    if (rank == 0) {
        //printf("Execution Time: %f seconds\n", time);
        printf("%f\n", time);
        write_data(prev_x, "grav_data/result1000/outx.double", np);
        write_data(prev_y, "grav_data/result1000/outy.double", np);
        write_data(prev_z, "grav_data/result1000/outz.double", np);
    }

    free(m);
    free(prev_x); free(prev_y); free(prev_z);
    free(local_next_x); free(local_next_y); free(local_next_z);
    free(local_prev_x); free(local_prev_y); free(local_prev_z);
    free(local_prev_vx); free(local_prev_vy); free(local_prev_vz);

    MPI_Finalize();
    return 0;
}
