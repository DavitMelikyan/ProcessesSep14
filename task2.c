#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

typedef struct {
    int flag;
    char* msg;
} arr;

int main() {
    arr obj;
    obj.msg = mmap(NULL,4096,PROT_WRITE | PROT_READ,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (obj.msg == MAP_FAILED) {
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
        printf("Child - %s\n", obj.msg);
        munmap(obj.msg, 4096);
        return 0;
    }
    else {
        const char *str = "Hello from Parent";
        memcpy(obj.msg, str, 4096);
        obj.flag = 1;
        wait(NULL);
        printf("Parent Process\n");
        munmap(obj.msg, 4096);
    } 
}