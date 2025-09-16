#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main() {
    char* ptr = mmap(NULL,4096,PROT_WRITE | PROT_READ,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return -1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    else if (pid == 0) {
        printf("Child - %s\n", ptr);
        munmap(ptr, 4096);
        return 0;
    }
    else {
        const char *str = "Hello from Parent";
        memcpy(ptr, str, 4096);
        wait(NULL);
        printf("Parent Process\n");
        munmap(ptr, 4096);
    } 
}