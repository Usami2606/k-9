#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

double second();

#define M 500
#define K 500
#define N 500

double A[M][K];
double B[K][N];
double C[M][N];

void initialize_matrices() {
    int i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < K; j++)
            A[i][j] = (double)(i + j);

    for (i = 0; i < K; i++)
        for (j = 0; j < N; j++)
            B[i][j] = (double)(i - j);
}

void matrix_multiply() {
    int i, j, k;
#pragma omp parallel for private(j, k) shared(A, B, C)
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            double sum = 0.0;
            for (k = 0; k < K; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    double start, end;
    double times[20];  // Array to store measurement time
    int i;
    int t;
    for (t = 0; t < 20; t++) {
        initialize_matrices();

        start = second();
        matrix_multiply();
        end = second();

        times[t] = end - start;
    }

    // Calculate average, max, min
    double total = 0.0, max_time = times[0], min_time = times[0];
    for (i = 0; i < 20; i++) {
        total += times[i];
        if (times[i] > max_time) max_time = times[i];
        if (times[i] < min_time) min_time = times[i];
    }

    printf("Average time = %f seconds\n", total / 20.0);
    printf("Maximum time = %f seconds\n", max_time);
    printf("Minimum time = %f seconds\n", min_time);

    return 0;
}

double second() {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    return (double)(tm.tv_sec) + (double)(tm.tv_usec) / 1.0e6;
}
