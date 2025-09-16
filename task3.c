#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main() {
    int* ptr = mmap(NULL,4096,PROT_WRITE | PROT_READ,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    const int size = 12;
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
        for (int i = 0; i < size; ++i) {
            printf("%d ", ptr[i]);
        }
        printf("\n");
        munmap(ptr, 4096);
        return 0;
    }
    else {
        int arr[size] = {1,2,3,4,5,6,7,8,9,10,11,12};
        memcpy(ptr, arr, 4096);
        wait(NULL);
        printf("Parent Process\n");
        munmap(ptr, 4096);
    } 
}