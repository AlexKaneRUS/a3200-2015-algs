#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <memory.h>
#include <fcntl.h>
#include <zconf.h>

#define true 1
#define false 0

int graph[][2] = {
        {0, 1},
        {1, 3},
        {0, 2},
        {0, 3}
};

void dfs(int* visited, int vertex){
        visited[vertex] = true;
        int i = 0;
        for (i; i < 4; ++i){
            if (graph[i][0] == vertex && visited[graph[i][1]] == false){
                visited[graph[i][1]] = true;
                pid_t a = fork();
                if (a == -1){
                    fprintf(stderr, "Yo! U don't have enough memory, man!\n");
                } else
                if (a == 0){
                    printf("Process %i is going to visit vertex number %i\n", getpid(), graph[i][1]);
                    dfs(visited, graph[i][1]);
                } else {
                    printf("Process %i forked! Child pid: %i\n", getpid(), a);
                }
            }
        }
    }

int main() {
    printf("Parent process: %i\n", getpid());
    int memery = shmget(0, 4 * sizeof(int), IPC_CREAT | 0666);
    if (memery == -1){
        fprintf(stderr, "Your computer is old, man! Or you're using python. Either way, it's bad!");
        return 1;
    }
    int* visited = (int*) shmat(memery, 0, 0);
    memset(visited, 0, 4 * sizeof(int));
    dfs(visited, 0);
    return 0;
}

