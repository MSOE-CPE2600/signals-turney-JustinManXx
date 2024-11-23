/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by:
 * Justin Mahr
 * Brief summary of modifications:
 * Removed exit(1) in handle_signal
 * Added the ability to print the signal to the console
 * use kill -9 <PID> to exit program now
 * ps aux | grep 'signal_handler' to get the PID
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message and exits
 */
void handle_signal() {
    printf("Received a signal: %d\n", SIGINT);
}

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}