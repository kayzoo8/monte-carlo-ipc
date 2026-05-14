
/*
* Define the data structures that will travel through the pipes.
* - WorkerConfig: A struct containing the number of trials and a seed.
* - WorkerResult: A struct containing hits (long long) and total_samples (long long).
*           By sending a struct through the pipe, you keep the communication "clean."
*/


#ifndef MONTE_CARLO_IPC_TYPES_H
#define MONTE_CARLO_IPC_TYPES_H

typedef struct {
    int worker_id; // for debugging
    long long total_trials; // the N iterations the child performed
    long long hits; // how many landed inside d^2 <= 1
    double elapsed_time; // how long child took
} sim_result;

#endif //MONTE_CARLO_IPC_TYPES_H
