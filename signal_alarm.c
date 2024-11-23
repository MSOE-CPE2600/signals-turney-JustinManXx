/**
 * File: signal_alarm.c
 * Modified by:
 * Justin Mahr
 * Brief summary of program:
 * Initializes the alarm signal, and waits once it recieves the proper signal
 * It will trigger the alarm to go off after 5 seconds then exit the program.
 */

#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Signal handler function
void handle_alarm(int sig) {
    if (sig == SIGALRM) {
        printf("SIGALRM received: Alarm in 5 seconds.\n");
    }
}

int main() {
    // Register the signal for SIGALRM
    if (signal(SIGALRM, handle_alarm) == SIG_ERR) {
        perror("Error setting up signal handler");
        return 1;
    }

    // Wait 5 seconds
    printf("Alarm will go off in 5 seconds...\n");
    alarm(5);

    // Wait
    pause();

    printf("Thank you, Exiting program....\n");
    return 0;
}
