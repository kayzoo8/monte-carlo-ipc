#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/types.h"

#define NUM_ITERATIONS 100000

/*
 * logic:
 * - functions to create pipes
 * - handle fork()
 * - ensure file descriptors are closed correctly
 * Concurrency: A function that spawns N workers and maps each to a specific pipe.
 */

void create_pipes(int pipes[][2], int num_workers) {
    // int pipes[num_workers][2];

    for (int i = 0; i < num_workers; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
        int pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        // child will write, parent will read

        if (pid == 0) { // child
            if (close(pipes[i][0]) == -1) { // close read
                perror("close");
                exit(1);
            }

            compute_pi_samples(NUM_ITERATIONS, pipes[i][1]);
            if (close(pipes[i][1]) == -1) { // close child write
                perror("close");
                exit(1);
            }
            exit(EXIT_SUCCESS);
        }
        // parent
        if (close(pipes[i][1]) == -1) { // close write
            perror("close");
            exit(1);
        }
    }
}
