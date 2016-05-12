#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>
#include <zconf.h>
#include <pthread.h>

#define true 1
#define false 0

struct arg_struct{
    int* visited;
    int vertex;
    pthread_t* threads;
};

int graph[][2] = {
        {0, 1},
        {1, 3},
        {0, 2},
        {2, 3},
        {2, 6},
        {3, 6},
        {3, 4},
        {3, 5},
        {4, 5},
        {5, 6},
        {5, 6},
};

void* dfs(void *arguments){
    struct arg_struct *args = arguments;
    if (!args->visited[args->vertex]){
        args->visited[args->vertex] = true;
        int i = 0;
        for (i = 0; i < 11; ++i){
            if (graph[i][0] == args->vertex){
                struct arg_struct new_args;
                new_args.visited = args->visited;
                new_args.vertex = graph[i][1];
                new_args.threads = args->threads;
printf("Going to vertex %i\n", graph[i][1]);
                args->visited[11]++;                
                pthread_create(&args->threads[args->visited[11] - 1], NULL, dfs, (void *)&new_args);
		pthread_join(args->threads[args->visited[11] - 1], NULL);	
            }
        }	
            return 0;
    }
    else{
        return 0;
    }
}

int main() {
    int memery = shmget(0, 12 * sizeof(int), IPC_CREAT | 0666);
    if (memery == -1){
        fprintf(stderr, "Your computer is old, man! Or you're using python. Either way, it's bad!\n");
        return 1;
    }
    int* visited = (int*) shmat(memery, 0, 0);
    memset(visited, 0, 12 * sizeof(int));
int memery1 = shmget(0, 11 * sizeof(pthread_t), IPC_CREAT | 0666);
    if (memery1 == -1){
        fprintf(stderr, "Your computer is old, man! Or you're using python. Either way, it's bad!\n");
        return 1;
    }
    pthread_t* threads = (pthread_t*) shmat(memery1, 0, 0);
    memset(threads, 0, 11 * sizeof(pthread_t));
    struct arg_struct new_args;
    new_args.visited = visited;
    new_args.vertex = 0;
    new_args.threads = threads;
printf("Going to do my business\n");
    dfs((void *)&new_args);
    printf("Number of threads: %i\n", visited[11]);
    return 0;
}

