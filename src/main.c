#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * will orchestrate everything
 * - parses command-line arguments
 * - calls the ipc_manager to spawn workers
 * - uses a loop to read results from the pipe
 * - aggregates data and calculates the final π and confidence interval
 */


