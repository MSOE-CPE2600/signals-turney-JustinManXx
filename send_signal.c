/**
 * File: send_signal.c
 * Modified by:
 * Justin Mahr
 * Brief summary of program:
 * You can use ps aux | grep '[r]ecv_signal' after ./recv_signal
 *      running to get the PID of it, and then input that as the arguement
 *      when running the send_signal program
 * 
 * This program takes a command line PID to send a signal to a reciever
 * It also generates a random integer 0-99 to send with the signal
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    // Seed
    srand(time(NULL));

    // PID argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    // Convert PID to integer
    pid_t pid = atoi(argv[1]);
    if (pid <= 0) {
        fprintf(stderr, "Error: Invalid PID: %s\n", argv[1]);
        return 1;
    }

    // Generate a random integer between 0 and 99
    int randomValue = rand() % 100; 
    printf("Sending SIGUSR1 with value: %d to PID: %d\n", randomValue, pid);

    // Signal Structure
    union sigval value;
    value.sival_int = randomValue;

    // Send the signal & the random value
    if (sigqueue(pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        return 1;
    }

    return 0;
}
