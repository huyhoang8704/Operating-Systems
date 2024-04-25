#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define FILENAME "shared_file.txt"
#define FILESIZE 4096  // Size of the shared memory file

int main() {
    int fd;
    pid_t pid;
    char *shared_memory;

    fd = open(FILENAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd, FILESIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    shared_memory = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // tạo process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        printf("Child process share memory: \n");

        // Write data to the shared memory
        sprintf(shared_memory, "Hello from the child process!");

        printf("Child process wrote data to share memory:\n");

        // Unmap the shared memory
        if (munmap(shared_memory, FILESIZE) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        printf("Child process completed.\n");
    } else { // Parent process
        printf("Parent process waiting for child...\n");
        wait(NULL); // Wait for the child process to finish

        printf("Parent process reading from shared memory...\n");

        // Read data from the shared memory
        printf("Parent process received: %s\n", shared_memory);

        // Unmap the shared memory
        if (munmap(shared_memory, FILESIZE) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        // Remove the file
        if (remove(FILENAME) == -1) {
            perror("remove");
            exit(EXIT_FAILURE);
        }

        printf("Parent process completed.\n");
    }

    return 0;
}

