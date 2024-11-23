/**
 * File: tennis_reciever.c
 * Modified by:
 * Justin Mahr
 * Brief summary of program:
 * tennis_reciever.c is the "bot", this program initializes and waits for
 * a signal from the sender.
 * After which they will send signals back and forth hiting or 
 * missing until one player reaches 21 points then the game will end.
 */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

// Score variables
int playerScore = 0;
int opponentScore = 0;
int hitNumber = 0;

// Function Prototypes
void checkScore();
int hitChance();

/**
 * This function handles the signals
 */
void handle_signal(int sig, siginfo_t *info, void *context) {
    (void)context;

    // Check if the signal indicates a miss
    int missed = info->si_value.sival_int;

    if (missed) {
        printf("Player missed! Bot scores a point.\n");
        opponentScore++;
        union sigval sig_value = {.sival_int = 0}; // 0 indicates a hit
            if (sigqueue(info->si_pid, SIGUSR1, sig_value) == -1) {
                perror("sigqueue");
            }
    } else {

        // Print & incriment volley number
        hitNumber++;
        printf("Hit number: %d (Bot)\n", hitNumber);

        // Simulate a real tennis match feeling
        printf("Bot hitting back to Player ::: PID %d\n", info->si_pid);
        int wait_time = rand() % 2 + 1; 
        sleep(wait_time);

        // Randomize hit chance
        int hit = hitChance();
        if (!hit) {
            printf("Bot missed!\n");
            playerScore++;
            printf("Player's point! Player's score: %d\n", opponentScore);

            // Notify Player of the miss
            union sigval sig_value = {.sival_int = 1}; // 1 indicates a miss
            if (sigqueue(info->si_pid, SIGUSR1, sig_value) == -1) {
                perror("sigqueue");
            }
        } else {
            // Notify Player of the hit
            union sigval sig_value = {.sival_int = 0}; // Indicates a hit
            if (sigqueue(info->si_pid, SIGUSR1, sig_value) == -1) {
                perror("sigqueue");
            }
        }
    }
    checkScore();
}


int main() {
    srand(time(NULL));

    // Set up the signal structure
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        exit(1);
    }
    // Wait for a signal
    printf("Bot waiting for ball ::: PID: %d\n", getpid());
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
