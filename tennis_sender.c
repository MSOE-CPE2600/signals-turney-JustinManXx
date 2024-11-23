/**
 * File: tennis_sender.c
 * Modified by:
 * Justin Mahr
 * Brief summary of program:
 * tennis_sender is the "player", this program initializes and sends a signal
 * to the PID. After which they will send signals back and forth hiting or 
 * missing until one player reaches 21 points then the game will end.
 */
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


// Score variables
int playerScore = 0;
int opponentScore = 0;

// Function Prototypes
void checkScore();
int hitChance();

/**
 * This function handles the signals
 */
void handle_signal(int sig, siginfo_t *info, void *context) {
    (void)sig;
    (void)context;

    // Look to see if the signal sent indicates a miss
    int missed = info->si_value.sival_int;

    if (missed) {
        printf("Bot missed! Player scores a point.\n"); 
        playerScore++;
        union sigval sig_value = {.sival_int = 0}; // 0 indicates a hit
            if (sigqueue(info->si_pid, SIGUSR1, sig_value) == -1) {
                perror("sigqueue");
            }
    } else {

        // Wait a time for the hit back like a real tennis match
        printf("Player hitting back to Bot ::: PID %d\n", info->si_pid);
        int wait_time = rand() % 2 + 1; 
        sleep(wait_time);

        // Set hit chance
        int hit = hitChance();
        if (!hit) {
            printf("Player missed!\n");
            opponentScore++;
            printf("Bot's point! Bot's score: %d\n", opponentScore);

            // Notify Bot of the miss
            union sigval sig_value = {.sival_int = 1}; // 1 indicates a miss
            if (sigqueue(info->si_pid, SIGUSR1, sig_value) == -1) {
                perror("sigqueue");
            }
        } else {
            // Notify successful hit
            union sigval sig_value = {.sival_int = 0}; // 0 indicates a hit
            if (sigqueue(info->si_pid, SIGUSR1, sig_value) == -1) {
                perror("sigqueue");
            }
        }
    }
    checkScore(); 
}



int main(int argc, char *argv[]) {

    // Check for pid arguement
    if (argc < 2) {
        printf("Usage: ./tennis_sender <receiver_pid>\n");
        exit(1);
    }

    pid_t receiver_pid = atoi(argv[1]);

    // Set up the signal handler
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error setting up signal handler in sender");
        exit(1);
    }

    printf("Player is hitting ::: PID %d\n", getpid());

    // Send signal to receiver
    union sigval sig_value = {.sival_int = 0};  // 0 means a hit
    if (sigqueue(receiver_pid, SIGUSR1, sig_value) == -1) {
        perror("sigqueue failed to send signal to receiver");
        exit(1);
    }
    printf("Signal sent successfully.\n");

    // Wait for response
    printf("Waiting for response...\n");
    while (1) {
        pause(); 
    }

    return 0;
}

/**
 * Checks to see if someone has won yet, if someone has won exits the game
 */
void checkScore() {
    if (playerScore >= 21 || opponentScore >= 21) {
        printf("GAME OVER!!!\n");
        if (playerScore > opponentScore) {
            printf("Bot Won with %d to %d\n", opponentScore, playerScore);
        } else {
            printf("Player Won with %d to %d\n", playerScore, opponentScore);
        }
        exit(0);
    }
    printf("Bot Score: %d ::: Player's Score: %d\n", opponentScore, playerScore);
}

/**
 * Sets the hit chance of the players
 */
int hitChance() {
    return rand() % 100 < 50; // 50% chance of hitting
}