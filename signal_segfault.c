/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Jim Luzano-Belfield
 * Course: CPE-2600, Section: 111
 * Assignment: Lab 10 - Signals
 *
 * Brief summary of modifications:
 *   - Installed a handler for SIGSEGV that prints a message and returns
 *     without doing anything else.
 *
 * Observed behavior:
 *   The message "Received a segmentation fault (SIGSEGV)" prints over and
 *   over without stopping, and the printf of *i never completes.
 *
 * Why:
 *   When a handler returns, execution resumes at the exact instruction that
 *   was interrupted. For SIGSEGV that is the faulting load from address NULL.
 *   Nothing has changed (i is still NULL), so the load faults again, the OS
 *   sends SIGSEGV again, the handler runs again, and so on forever.
 *   Stop it with Ctrl+C (SIGINT is not handled, so its default action,
 *   terminate, applies) or kill -9 <pid>.
 */

#include <signal.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGSEGV - prints a message and returns
 * @param sig the signal number that was received
 */
void handle_segfault(int sig) {
    printf("Received a segmentation fault (SIGSEGV, signal %d)\n", sig);
}

int main (int argc, char* argv[]) {
    (void)argc;   // unused
    (void)argv;   // unused

    // Install the handler for segmentation faults
    signal(SIGSEGV, handle_segfault);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}
