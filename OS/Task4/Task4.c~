#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>
#include <zconf.h>
#include <time.h>
#include <stdlib.h>

#define n 228


int execute(int* array){
    pid_t a = fork();
    if (a == -1){
        fprintf(stderr, "Yo! U don't have enough memory, man!\n");
    } else
    if (a == 0){
        printf("Process %i is generating\n", getpid());
        int a = 0;
        while(array[2 * n]){
            int i = 0;
            for (i; i < n; i++){
                srand(time(NULL));
                array[i] = a;
                a++;
            }
        }
        printf("Stopped");
        return 0;
    }

    pid_t b = fork();
    if (b == -1){
        fprintf(stderr, "Yo! U don't have enough memory, man!\n");
    } else
    if (b == 0){
        printf("Process %i is calculating\n", getpid());
        while(array[2 * n]){
            int i = n;
            for (i; i < 2 * n - 1; i++){
                array[i] = array[i - n] + array[i - n + 1];
            }
        }
        printf("Stopped");
        return 0;
    }

    pid_t c = fork();
    if (c == -1){
        fprintf(stderr, "Yo! U don't have enough memory, man!\n");
    } else
    if (c == 0){
        printf("Process %i is printing\n", getpid());
        while(array[2 * n]){
            int i = n;
            for (i; i < 2 * n - 1; i++){
                    printf("Result is %i\n", array[i]);
            }
        }
        printf("Stopped");
        return 0;
    }

    int stop = getchar();
    if (stop == 115){
        printf("Stopped");
        array[2 * n] = 0;
        wait(a);
        wait(b);
        wait(c);
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
    array[2 * n] = 1;
    execute(array);
    return 0;
}
