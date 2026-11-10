/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by: Jim Luzano-Belfield
 * Course: CPE-2600, Section: 111
 * Assignment: Lab 10 - Signals
 *
 * Brief summary of modifications:
 *   - The handler no longer calls exit(). It prints a message and returns, so
 *     the program goes back to its sleep loop after every SIGINT.
 *   - Because SIGINT (Ctrl+C) no longer ends the program, stop it with
 *     SIGKILL, which cannot be caught or ignored:
 *         kill -9 <pid>      (or: kill -SIGKILL <pid>)
 *   - Two ways to send SIGINT to this process:
 *         1. Press Ctrl+C in the terminal running it
 *         2. From another terminal: kill -SIGINT <pid>   (or kill -2 <pid>)
 *   - main() prints its pid so it is easy to target with kill.
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message and returns
 * @param sig the signal number that was received
 */
void handle_signal(int sig) {
    printf("Received a signal (%d) - not exiting\n", sig);
}

int main() {

    printf("signal_handler running, pid = %d\n", getpid());

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}
