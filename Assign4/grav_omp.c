#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <math.h>
#include <omp.h>
#include "grav_data/data_util_bin.c"

double sencond();

double second() {
    struct timeval tm;
    double t;

    gettimeofday(&tm, NULL);
    t = (double)(tm.tv_sec) + ((double)(tm.tv_usec)) / 1.0e6;
    return t;
}

int main(){
    int np = 1000;

    double *m = malloc(sizeof(double) * np);
    double *prev_x = malloc(sizeof(double) * np);
    double *prev_y = malloc(sizeof(double) * np);
    double *prev_z = malloc(sizeof(double) * np);
    double *next_x = malloc(sizeof(double) * np);
    double *next_y = malloc(sizeof(double) * np);
    double *next_z = malloc(sizeof(double) * np);
    double *prev_vx = malloc(sizeof(double) * np);
    double *prev_vy = malloc(sizeof(double) * np);
    double *prev_vz = malloc(sizeof(double) * np);

    read_data("grav_data/n1000/m.double", m, np);
    read_data("grav_data/n1000/x.double", prev_x, np);
    read_data("grav_data/n1000/y.double", prev_y, np);
    read_data("grav_data/n1000/z.double", prev_z, np);
    read_data("grav_data/n1000/vx.double", prev_vx, np);
    read_data("grav_data/n1000/vy.double", prev_vy, np);
    read_data("grav_data/n1000/vz.double", prev_vz, np);

    double dt = 1;
    double G = 1;
    int STEP = 10;
    int TIMESTEP = 0;

    double start = second();

    for (TIMESTEP = 0; TIMESTEP < STEP; TIMESTEP++) {
        int i = 0;
#pragma omp parallel for
        for(i = 0; i < np; i++) {
            double x = prev_x[i];
            double y = prev_y[i];
            double z = prev_z[i];

            double next_vx = 0;
            double next_vy = 0;
            double next_vz = 0;

            int j = 0;
            for (j = 0; j < np; j ++) {
                double r = sqrt(pow(prev_x[j] - x, 2) + pow(prev_y[j] - y, 2) + pow(prev_z[j] - z, 2));
                if (j == i) {
                    continue;
                }

                double ax = G * m[j] / pow(r, 3) * (prev_x[j] - x);
                double ay = G * m[j] / pow(r, 3) * (prev_y[j] - y);
                double az = G * m[j] / pow(r, 3) * (prev_z[j] - z);

                next_vx += ax * dt;
                next_vy += ay * dt;
                next_vz += az * dt;
            }

            next_vx += prev_vx[i];
            next_vy += prev_vy[i];
            next_vz += prev_vz[i];

            next_x[i] = x + next_vx * dt;
            next_y[i] = y + next_vy * dt;
            next_z[i] = z + next_vz * dt;
            prev_vx[i] = next_vx;
            prev_vy[i] = next_vy;
            prev_vz[i] = next_vz;
        }

        double *compare;
        compare = prev_x;
        prev_x = next_x;
        next_x = compare;

        compare = prev_y;
        prev_y = next_y;
        next_y = compare;

        compare = prev_z;
        prev_z = next_z;
        next_z = compare;
    }

    double time = second() - start;
    printf("%f\n", time);

    write_data(prev_x, "grav_data/result1000/outx.double", np);
	write_data(prev_y, "grav_data/result1000/outy.double", np);
	write_data(prev_z, "grav_data/result1000/outz.double", np);

}