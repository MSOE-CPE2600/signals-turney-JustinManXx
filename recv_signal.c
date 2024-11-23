/**
 * File: recv_signal.c
 * Modified by:
 * Justin Mahr
 * Brief summary of program:
 * Recieves a signal from send_signal
 * The program waits in a infinite loop until it recieves a signal
 * 
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Signal handler function
void handle_sigusr1(int sig, siginfo_t *si, void *uc) {
    if (sig == SIGUSR1) {
        printf("Received SIGUSR1 with value: %d\n", si->si_value.sival_int);
    }
}

int main() {

    // Print PID for user
    pid_t pid = getpid();
    printf("Process ID: %d\n", pid);

    // Initialize sigaction
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO; 
    sa.sa_sigaction = handle_sigusr1;

    // Register the signal handler
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for SIGUSR1\n");

    // Wait for signals
    while (1) {
        pause(); 
    }

    return 0;
}
