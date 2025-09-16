#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
} Arr;

int isPrime(int number) {
    for (int i = 2; i < number; i++) {
        if (number % i == 0 && i != number)
            return 0;
    }
    return 1;
}

void* func1(void* arg) {
    int size = ((Arr*)arg)->size;
    int* arr1 = (int*) malloc(size * sizeof(int));
    int j = 2;
    for (int i = 0; i < size; ++i) {
        while(!isPrime(j)) ++j;
        arr1[i] = j++;
    }
    ((Arr*)arg)->arr = arr1;
    return NULL;
}

void* func2(void* arg) {
    int* arr = ((Arr*)arg)->arr;
    for (int i = 0; arr[i]; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return NULL;
}

int main() {
    pthread_t th1;
    pthread_t th2;
    Arr arg = {NULL, 10};
    pthread_create(&th1,NULL,func1,&arg);
    pthread_join(th1, NULL);
    pthread_create(&th2,NULL,func2,&arg);
    pthread_join(th2, NULL);
    return 0;
}

