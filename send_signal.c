/**
 * File: send_signal.c
 * Modified by: Jim Luzano-Belfield
 * Course: CPE-2600, Section: 111
 * Assignment: Lab 10 - Signals
 *
 * Brief summary of program:
 *   Sending half of Part 4. Takes the receiver's pid on the command line
 *   (converted with atoi), seeds the random number generator with
 *   srand(time(NULL)), picks a random integer, prints it, and sends it to the
 *   receiver along with SIGUSR1 using sigqueue.
 *
 * Usage:
 *     ./send_signal <pid of recv_signal>
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Need exactly one argument: the receiver's pid
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    // Convert the command-line string to a pid
    pid_t target = atoi(argv[1]);
    if (target <= 0) {
        fprintf(stderr, "Invalid pid: %s\n", argv[1]);
        return 1;
    }

    // Seed with the current time so each run gives a different number
    srand(time(NULL));
    int number = rand();

    // Package the number as the signal's value
    // Zero the whole union first: sival_int only fills 4 of its 8 bytes
    union sigval value;
    memset(&value, 0, sizeof(value));
    value.sival_int = number;

    printf("Sending SIGUSR1 to pid %d with value: %d\n", target, number);

    if (sigqueue(target, SIGUSR1, value) == -1) {
        perror("sigqueue");
        return 1;
    }

    return 0;
}
