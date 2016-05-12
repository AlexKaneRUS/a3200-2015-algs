//
// Created by alexkane on 5/11/16.
//
// gcc -pthread -o Task6 Task6.c

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <memory.h>
#include <zconf.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define n 228

struct the_array{
    int* itself;
};

void* generate(void* arguments){
    struct the_array *args = arguments;
    int a = 0;
    while(args->itself[2 * n]){
        int i = 0;
        for (i; i < n; i++){
            srand(time(NULL));
            args->itself[i] = a;
            a++;
        }
    }
    return 0;
}

void* calculate(void* arguments){
    struct the_array *args = arguments;
    while(args->itself[2 * n]){
        int i = n;
        for (i; i < 2 * n - 1; i++){
            args->itself[i] = args->itself[i - n] + args->itself[i - n + 1];
        }
    }
    return 0;
}

void* print(void* arguments){
    struct the_array *args = arguments;
    while(args->itself[2 * n]){
        int i = n;
        for (i; i < 2 * n - 1; i++){
            printf("Result is %i\n", args->itself[i]);
        }
    }
    return 0;
}

int execute(int* array, pthread_t* threads){
    struct the_array new_array;
    new_array.itself = array;
    pthread_create(&threads[0], NULL, generate, (void *) &new_array);
    pthread_create(&threads[1], NULL, calculate, (void *) &new_array);
    pthread_create(&threads[2], NULL, print, (void *) &new_array);
    int stop = getchar();
    if (stop == 115){
        array[2 * n] = 0;
        shmdt(array);
        return 0;
    }
}

int main() {
    int memery = shmget(0, 2 * n * sizeof(int) + sizeof(int), IPC_CREAT | 0666);
    if (memery == -1){
        fprintf(stderr, "Your computer is old, man! Or you're using python. Either way, it's bad!");
        return 1;
    }
    int* array = (int*) shmat(memery, 0, 0);
    memset(array, 0, 2 * n * sizeof(int));
    int memery1 = shmget(0, 3 * sizeof(pthread_t), IPC_CREAT | 0666);
    if (memery1 == -1) {
        fprintf(stderr, "Your computer is old, man! Or you're using python. Either way, it's bad!\n");
        return 1;
    }
    pthread_t *threads = (pthread_t *) shmat(memery1, 0, 0);
    memset(threads, 0, 3 * sizeof(pthread_t));
    array[2 * n] = 1;
    execute(array, threads);
    return 0;
}

