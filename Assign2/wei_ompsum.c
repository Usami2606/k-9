#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>

double second();

#define N 10000000

double A[N];

double sum(double *a, int n) {
    int i;
    double s = 0.0;
#pragma omp parallel
{
#pragma omp for reduction(+:s)
    for (i = 0; i < n; i++) s += a[i];
}
    return s;
}

int main() {
    double start, end;
    double times[20];
    int i,j;

    // Take 20 measurements
    for (j = 0; j < 20; j++) {
        start =second();
#pragma omp parallel for
        for (i = 0; i < N; i ++) {
            double m = (double)(i + 1);
            A[i] = (1.0 / m) * sin(1.0 / m);
        }
        sum(A, N);
        end  = second();
        times[j] = end -start;
    }

    // Calculate the average, maximum, and minimum
    double total_time = 0.0;
    double max_time = times[0];
    double min_time = times[0];

    for (i = 0; i < 20; i++) {
        total_time += times[i];
        if (times[i] > max_time) max_time = times[i];
        if (times[i] < min_time) min_time = times[i];
    }

    double average_time = total_time / 20.0;

    // Output results
    printf("Average time = %f seconds\n", average_time);
    printf("Maximum time = %f seconds\n", max_time);
    printf("Minimum time = %f seconds\n", min_time);

    return 0;
}

double second() {
    struct timeval tm;
    double t;

    gettimeofday(&tm, NULL);
    t = (double)(tm.tv_sec) + ((double)(tm.tv_usec)) / 1.0e6;
    return t;
}