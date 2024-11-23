/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by:
 * Justin Mahr
 * Brief summary of modifications:
 * Added a handler for SIGSEGV, which prints out an error has occured
 * Added a intialization of the signal handler for SIGSEGV in main
 * If the user wishes for the program to end after Segmentation faulting they 
 *      can use "exit(1);"
 */


#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV: A segmetnation fault has occured\n");
    //exit(1);
}

int main (int argc, char* argv[]) {
    // Initialize signal handler for SIGSEGV
    signal(SIGSEGV, handle_sigsegv);

    // Null pointer reference
    int* i = NULL;

    // Dereference the null pointer causing an infinite loop
    printf("The value of i is: %d\n", *i);

    return 0;
}