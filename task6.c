#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
    int *arr;
    int size;
} Arr;

void* sum(void* arg) {
    Arr* array = (Arr*) arg;
    if (array->size == 0) {
        printf("The array is empty\n");
        return NULL;
    }
    int sum = 0;
    for (int i = 0; i < array->size; i++) {
        sum += array->arr[i];
    }
    printf("Sum is - %d\n", sum);
    return NULL;
}

int main() {
    const int size = 5;
    int arr[size] = {1,2,3,4,5};
    pid_t pid = fork();
    if (pid == 0) {
        pthread_t th;
        Arr args = {arr, size};
        pthread_create(&th, NULL, sum, &args);
        pthread_join(th, NULL);
    } else {
        wait(NULL);
    }
}