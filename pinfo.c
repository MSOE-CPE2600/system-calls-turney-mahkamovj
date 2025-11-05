/* File: pinfo.c
 * Name: Jaffar Mahkamov
 * Course: CPE-2600 - 111
 * Assignment: Lab 9 
 * 
 * This program prints information about a process.
 * If a PID is given on the command line,
 * it shows information about that process.
 * If no PID is given, it shows info for the current process.
 * 
 * How to compile: 
 *    make
 *    ./pinfo
 */

#define _GNU_SOURCE  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sched.h>



int main(int argc, char* argv[])
{
    pid_t pid;     // Process ID to inspect
    int priority;  // Process priority
    int policy;    // Scheduling policy number

    // Determine which process to look up
    if (argc == 2) {
        pid = atoi(argv[1]);
    } else if (argc == 1) {
        pid = getpid();  // current process
    } else {
        printf("Usage: %s [pid]\n", argv[0]);
        return 1;
    }

    // Get the process priority
    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);

    if (errno != 0) {
        perror("Error getting process priority");
        return 1;
    }

    //get the scheduling policy
    policy = sched_getscheduler(pid);

    if (policy == -1) {
        perror("Error getting scheduling policy");
        return 1;
    }

    //Print process ID and priority
    printf("Process ID: %d\n", pid);
    printf("Priority: %d\n", priority);

    // Convert and print the scheduling policy
    if (policy == SCHED_OTHER) {
        printf("Scheduling Policy: SCHED_OTHER (Normal)\n");
    } 
    else if (policy == SCHED_FIFO) {
        printf("Scheduling Policy: SCHED_FIFO (First-In First-Out)\n");
    } 
    else if (policy == SCHED_RR) {
        printf("Scheduling Policy: SCHED_RR (Round Robin)\n");
    } 
#ifdef SCHED_BATCH
    else if (policy == SCHED_BATCH){
        printf("Scheduling Policy: SCHED_BATCH (Batch Processing)\n");
    } 
#endif
#ifdef SCHED_IDLE
    else if (policy == SCHED_IDLE){
        printf("Scheduling Policy: SCHED_IDLE (Idle)\n");
    } 
#endif
    else {
        printf("Scheduling Policy:Unknown\n");
    }

    return 0;
}
