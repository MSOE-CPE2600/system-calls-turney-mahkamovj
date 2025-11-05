/* File: info.c
 * Name: Jaffar Mahkamov
 * Course: CPE-2600 - 111
 * Assignment: Lab 9 -System Calls
 * Uses POSIX information maintenance
 * system calls to print system and hardware information.
 *
 * How to compile:
 *   make
 *   ./info
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <time.h>



int main(int argc, char* argv[])
{
    //get the current time in nanoseconds
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        printf("current Time: %ld nanoseconds since the epoch\n", ts.tv_nsec);
    } else {
        perror("clock_gettime");
    }

    //Get the systems network name
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Hostname: %s\n", hostname);
    } else {
        perror("gethostname");
    }

    //get OS info
    struct utsname uts;
    if (uname(&uts) == 0) {
        printf("Operating system: %s\n", uts.sysname);
        printf("OS Release: %s\n", uts.release);
        printf("OS Version: %s\n", uts.version);
        printf("Hardware Type: %s\n", uts.machine);
    } else {
        perror("uname");
    }

    //Get cpu info
    long num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (num_cpus != -1){
        printf("Number of CPUs: %ld\n", num_cpus);
    } else {
        perror("sysconf(_SC_NPROCESSORS_ONLN)");
    }

    //Get memory 
    struct sysinfo info;
    if (sysinfo(&info) == 0){
        printf("Total Physical Memory: %lu bytes\n", info.totalram *info.mem_unit);
        printf("Free Physical Memory:  %lu bytes\n", info.freeram *info.mem_unit);
    } else{
        perror("sysinfo");
    }

    return 0;
}
