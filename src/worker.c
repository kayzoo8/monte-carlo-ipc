#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#include "../include/types.h"

/*
 * A function run_simulation(long long trials) that performs the dart-throwing loop.
 * Encapsulation: The worker shouldn't care about pipes. It should just return a
 * WorkerResult struct. This makes the logic unit-testable.
 */

void compute_pi_samples(long long iterations, int pipe_write_fd) {
    sim_result worker;
    worker.worker_id = getpid(); // worker id is pid for now
    worker.hits = 0;
    unsigned int seed = time(NULL) ^ (getpid() << 16);
        // generate diff sequence of random numbers unique to each worker
    for (int i = 0; i < iterations; i++) {
        double x = ((double) rand_r(&seed) / RAND_MAX) * 2 - 1;
        double y = ((double) rand_r(&seed) / RAND_MAX) * 2 - 1;
            // generate two random numbers between -1 and 1
        double distance = pow(x, 2) + pow(y, 2);
        if (distance <= 1) {
            worker.hits++;
        }
    }
    worker.total_trials = iterations;
    worker.elapsed_time = 0; // just for now
    if (write(pipe_write_fd, &worker, sizeof(sim_result)) == -1) {
        perror("write");
        exit(1);
    }
    exit(0);
}

sim_result test_math(long long iterations, unsigned int seed) {
    sim_result worker;
    worker.worker_id = getpid(); // worker id is pid for now
    worker.hits = 0;
    // unsigned int seed = time(NULL) ^ (getpid() << 16);
    // generate diff sequence of random numbers unique to each worker
    for (int i = 0; i < iterations; i++) {
        double x = ((double) rand_r(&seed) / RAND_MAX) * 2 - 1;
        double y = ((double) rand_r(&seed) / RAND_MAX) * 2 - 1;
        // generate two random numbers between -1 and 1
        double distance = pow(x, 2) + pow(y, 2);
        if (distance <= 1) {
            worker.hits++;
        }
    }
    worker.total_trials = iterations;
    worker.elapsed_time = 0; // just for now
    return worker;
}