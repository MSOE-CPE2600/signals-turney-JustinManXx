/**
 * File: signal_sigaction.c
 * Modified by:
 * Justin Mahr
 * Brief summary of program:
 * This is an example of using sigaction structure instead of a signal();
 * This structure allows for more advanced signal processing, such as
 * the tennis_volleying capabilities in tennis_sender.c
 */
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Signal handler function
void handle_sigusr1(int sig, siginfo_t *info, void *context) {
    (void)context;
    if (sig == SIGUSR1) {
        printf("SIGUSR1 received from process ID: %d\n", info->si_pid);
    }
}

int main() {
    struct sigaction sa;

    // Set up the structure
    sa.sa_sigaction = handle_sigusr1; 
    sa.sa_flags = SA_SIGINFO;        
    sigemptyset(&sa.sa_mask);       

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error setting up sigaction");
        return 1;
    }

    printf("Waiting for SIGUSR1... (Process ID: %d)\n", getpid());

    // wait
    while (1) {
        pause(); 
    }
    return 0;
}

