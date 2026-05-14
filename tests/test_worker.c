#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
# include "../include/types.h"
#include "../src/worker.c"

int main() {
    long long test_trials = 100000;
    unsigned int seed = 42;
    sim_result worker = test_math(test_trials, seed);

    double pi_est = 4.0 * ((double) worker.hits / worker.total_trials);

    printf("Trials: %lld\n", worker.total_trials);
    printf("Hits:   %lld\n", worker.hits);
    printf("Est PI: %f\n", pi_est);

    return 0;
}
