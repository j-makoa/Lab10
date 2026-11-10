/**
 * File: recv_signal.c
 * Modified by: Jim Luzano-Belfield
 * Course: CPE-2600, Section: 111
 * Assignment: Lab 10 - Signals
 *
 * Brief summary of program:
 *   Receiving half of Part 4. Uses sigaction with SA_SIGINFO to register a
 *   handler for SIGUSR1. When a SIGUSR1 sent with sigqueue arrives, the
 *   handler reads the integer that came with it (info->si_value.sival_int),
 *   prints it, and returns. main prints its pid (needed by send_signal) and
 *   then waits forever.
 *
 * Usage:
 *     ./recv_signal              (note the pid it prints)
 *     ./send_signal <that pid>   (in another terminal)
 *   Stop with Ctrl+C.
 */

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief SA_SIGINFO-style handler for SIGUSR1 - prints the value sent with it
 * @param sig the signal number that was received
 * @param info details about the signal, including the queued value
 * @param context the interrupted context (unused)
 */
void handle_usr1(int sig, siginfo_t *info, void *context) {
    (void)context;
    printf("Received SIGUSR1 (signal %d) from pid %d with value: %d\n",
           sig, info->si_pid, info->si_value.sival_int);
}

int main() {
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_sigaction = handle_usr1;   // three-argument handler
    action.sa_flags = SA_SIGINFO;        // required to receive si_value
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGUSR1, &action, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("recv_signal running, pid = %d\n", getpid());
    printf("Run: ./send_signal %d\n", getpid());

    // Wait forever; pause() sleeps until any signal arrives
    while (1) {
        pause();
    }

    return 0;
}
