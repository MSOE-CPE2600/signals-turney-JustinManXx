# Signal Handling Programs

This repository contains various C programs demonstrating signal handling in Linux. The programs include sending and receiving signals, simulating a simple tennis game using signals, handling segmentation faults, and utilizing alarms.

## Signal Research

### What is a signal disposition?
**Signal disposition** is the action taken by the operating system when a signal is received by a process. It determines how a process responds, which can include terminating, ignoring, or executing a specific function.

### What is a signal handler? What is it used for?
A **signal handler** is a user-defined function that executes in response to a specific signal. It allows developers to customize how a process responds to signals, enabling actions like cleanup, logging, or graceful termination.

### Default Dispositions
1. **Terminate**: The process is terminated immediately.
2. **Ignore**: The process ignores the signal.
3. **Core Dump**: A core dump is generated for debugging purposes.
4. **Stop**: The process is paused.
5. **Continue**: Resumes a previously stopped process.

## #Sending Signals Programmatically
You can send a signal to a process using the `signal` function in C.

**Example Code**:
```c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid = 12345; // Replace with the actual PID
    if (signal(pid, SIGTERM) == -1) {
        perror("Failed to send SIGTERM");
        exit(EXIT_FAILURE);
    }
    printf("SIGTERM sent to process %d\n", pid);
    return 0;
}
```

## Programs Overview

1. **recv_signal.c**
   - **Description**: Receives a signal from `send_signal.c` and waits indefinitely until a signal is received.
   - **Signal**: Handles `SIGUSR1` and prints the received value.

2. **send_signal.c**
   - **Description**: Sends a signal to a specified PID with a random integer (0-99) accompanying the signal.
   - **Usage**: Must be run with the PID of the receiving program.

3. **tennis_sender.c**
   - **Description**: Represents the player in a tennis game. Sends signals to the receiver (bot) and handles points scoring based on hits and misses.
   - **Usage**: Requires the PID of the receiving bot program as an argument.

4. **tennis_receiver.c**
   - **Description**: Represents the bot in the tennis game. Waits for signals from the sender and responds accordingly.
   - **Gameplay**: The game continues until one player reaches 21 points.

5. **signal_alarm.c**
   - **Description**: Sets an alarm signal that goes off after 5 seconds.
   - **Signal**: Handles `SIGALRM` and prints a message before exiting.

6. **signal_segfault.c**
   - **Description**: Demonstrates handling a segmentation fault by dereferencing a null pointer.
   - **Signal**: Handles `SIGSEGV` to print an error message.

7. **signal_handler.c**
   - **Description**: Sets a signal handler for `SIGINT` and prints a message when the signal is received.
   - **Usage**: Can be terminated using `kill -9 <PID>`.

## Compilation

To compile all the programs, you can use the provided `Makefile`. 

1. Open a terminal and navigate to the directory containing the source files.
2. Run the following command to compile the programs:
   ```bash
   make
    ```