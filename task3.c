#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

typedef struct {
    int flag;
    int* ptr;
} arr;

int main() {
    arr obj;
    obj.ptr = mmap(NULL,4096,PROT_WRITE | PROT_READ,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    const int size = 12;
    if (obj.ptr == MAP_FAILED) {
        perror("mmap");
        return -1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    else if (pid == 0) {
        while (!obj.flag) {
            sleep(1000);
        }
        for (int i = 0; i < size; ++i) {
            printf("%d ", obj.ptr[i]);
        }
        printf("\n");
        munmap(obj.ptr, 4096);
        return 0;
    }
    else {
        int arr[size] = {1,2,3,4,5,6,7,8,9,10,11,12};
        memcpy(obj.ptr, arr, 4096);
        obj.flag = 1;
        wait(NULL);
        printf("Parent Process\n");
        munmap(obj.ptr, 4096);
    } 
}