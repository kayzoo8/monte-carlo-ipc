#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include "../include/types.h"

#define MAX_BUF 10000

/*
 * will orchestrate everything
 * - parses command-line arguments
 * - calls the ipc_manager to spawn workers
 * - uses a loop to read results from the pipe
 * - aggregates data and calculates the final π and confidence interval
 */

int main(int argc, char **argv) {
    // only one argument which will be worker count

    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments\n");
        exit(1);
    }
    int num_workers = (int) strtol(argv[1], NULL, 10);
    int pipes[num_workers][2];
    create_pipes(pipes, num_workers);

    long long total_hits = 0;
    long long total_samples = 0;

    for (int i = 0; i < num_workers; i++) {
        // char results[MAX_BUF];
        sim_result results;
        while (read(pipes[i][0], &results, sizeof(sim_result)) > 0) {
            total_hits += results.hits;
            total_samples += results.total_trials;
        }
        if (close(pipes[i][0]) == -1) {
            perror("close");
            exit(1);
        }
    }

    for (int j = 0; j < num_workers; j++) {
        int status;
        if (wait(&status) == -1) {
            perror("wait");
            exit(1);
        }
        if (!WIFEXITED(status)) {
            // if failed
            fprintf(stderr, "Error: worker process\n");
            exit(1);
        }
    }
    // now estimate pi ~~ 4 * (hits/total)
    double est_pi = ((double) total_hits / (double) total_samples) * 4.0;

    // want to calculate confidence interval
    double conf_mult = sqrt(est_pi * (4 - est_pi) / (double) total_samples);
    double conf_low = est_pi - (1.96 * conf_mult);
    double conf_upp = est_pi + (1.96 * conf_mult);

    printf("Pi Estimate: %f\n", est_pi);
    printf("95%% CI: [%f, %f]\n", conf_low, conf_upp);

    return 0;
}
