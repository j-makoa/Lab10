/**
 * File: signal_alarm.c
 * Modified by: Jim Luzano-Belfield
 * Course: CPE-2600, Section: 111
 * Assignment: Lab 10 - Signals
 *
 * Brief summary of program:
 *   Registers a handler for SIGALRM, then calls alarm(5) to ask the operating
 *   system to send this process SIGALRM in 5 seconds. While waiting, main
 *   prints a countdown once per second. When the alarm goes off the handler
 *   prints that the signal was received and sets a flag so main can exit.
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// Set by the handler; volatile sig_atomic_t is safe to share with a handler
static volatile sig_atomic_t alarm_fired = 0;

/**
 * @brief Signal handler for SIGALRM - reports the alarm and sets the flag
 * @param sig the signal number that was received
 */
void handle_alarm(int sig) {
    printf("Received SIGALRM (signal %d) - the alarm went off!\n", sig);
    alarm_fired = 1;
}

int main() {
    // Register the handler before scheduling the alarm
    signal(SIGALRM, handle_alarm);

    // Ask the OS to send SIGALRM in 5 seconds
    alarm(5);
    printf("Alarm scheduled for 5 seconds from now\n");

    // Wait for the alarm, printing a simple counter each second
    int seconds = 0;
    while (!alarm_fired) {
        printf("Waiting... %d s\n", seconds);
        sleep(1);
        seconds++;
    }

    printf("Done, exiting\n");
    return 0;
}
