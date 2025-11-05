/*
 * Name: Jaffar Mahkamov
 * Course: CPE-2600 - 111
 * Assignment: Lab 9 - System Calls
 * File: finfo.c
 * Description:
 *   This program retrieves and displays information about a file.
 *
 * How to compile:
 *   make
 *   ./finfo filename
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[])
{
    //check for filename argument
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    struct stat fileStat;

    //open file
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Get file stats
    if (fstat(fd, &fileStat) == -1){
        perror("Error getting file information");
        close(fd);
        return 1;
    }

    //print file name and size
    printf("File: %s\n", filename);
    printf("Size: %lld bytes\n", (long long)fileStat.st_size);

    //determine file type
    printf("type: ");
    if (S_ISREG(fileStat.st_mode)){
        printf("Regular file\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("Symbolic link\n");
    } else if (S_ISCHR(fileStat.st_mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(fileStat.st_mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(fileStat.st_mode)) {
        printf("FIFO/pipe\n");
    } else if (S_ISSOCK(fileStat.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown\n");
    }

    // Print permissions (rwx style)
    printf("Permissions: ");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    //print owner and group
    printf("Owner UID: %d\n", fileStat.st_uid);
    printf("Group GID: %d\n", fileStat.st_gid);

    //print last modification time
    char* timeStr = ctime(&fileStat.st_mtime);
    if (timeStr != NULL){
        // Remove newline from ctime() output
        timeStr[strcspn(timeStr, "\n")] = '\0';
        printf("Last Modified: %s\n", timeStr);
    }

    close(fd);
    return 0;
}
