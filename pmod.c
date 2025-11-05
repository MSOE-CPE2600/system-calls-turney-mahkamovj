/*
 * Name: Jaffar Mahkamov
 * Course: CPE-2600 - 111
 * Assignment: Lab 9 - System Calls
 * File: pmod.c
 * Description:
 *   This program modifies its own process priority
 *   to reduce it by 10, sleeps for a specific time
 *   (1,837,272,638 nanoseconds), then prints a message.
 *
 * How to compile:
 *   make
 *   ./pmod
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <errno.h>


int main(int argc, char* argv[])
{
    int new_nice_value;
    struct timespec req;

    printf("Starting pmod program...\n");

    //Lower priority by 10 (increase niceness by +10)
    errno = 0;
    new_nice_value = nice(10);

    if (new_nice_value == -1 && errno != 0) {
        perror("Error changing priority with nice()");
        return 1;
    }

    printf("New nice value (priority): %d\n", new_nice_value);

    req.tv_sec = 1; // 1 second
    req.tv_nsec = 837272638; // remaining nanoseconds

    printf("Sleeping for  1.837 seconds..\n");

    if (nanosleep(&req, NULL) == -1) {
        perror("Error during nanosleep()");
        return 1;
    }

    printf("Goodbye\n");

    return 0;
}
