#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Start of the program\n");
    int pipe_parent[2], pipe_child[2], answer;
    size_t size;
    char answer_string[14];

    if (pipe(pipe_parent) < 0) {
        printf("Can not create the parent pipe\n");
        exit(-1);
    }

    if (pipe(pipe_child) < 0) {
        printf("Can not create the child pipe\n");
        exit(-1);
    }

    answer = fork();
    if (answer < 0) {
        printf("Can not fork the child\n");
        exit(-1);
    } else if (answer > 0) {
        close(pipe_parent[0]);
        close(pipe_child[1]);
        size = write(pipe_parent[1], "Hello, world!", 14);
        if (size != 14) {
            printf("Can not write all strings\n");
            exit(-1);
        }
        close(pipe_parent[1]);

        size = read(pipe_child[0], answer_string, 14);
        if (size != 14) {
            printf("Can not read from the child\n");
            exit(-1);
        }
        printf("Parent pulled from the child out: %s\n", answer_string);
        printf("Parent exit\n");
    } else {
        close(pipe_parent[1]);
        close(pipe_child[0]);
        size = read(pipe_parent[0], answer_string, 14);
        if (size < 0) {
            printf("Can not get from the parent\n");
            exit(-1);
        }
        printf("Pulled from the parent out: %s\n", answer_string);
	//Remake the string to make it more clear that we have 2 different options with "Hello world" string 
	int x = 13;
        for (int i = 0; i < x / 2; i++) {
        char t = answer_string[i];
        answer_string[i] = answer_string[x - i - 1];
        answer_string[x - i - 1] = t;
        }
        size = write(pipe_child[1], answer_string, 14);
        close(pipe_parent[0]);
        printf("Child exit\n");
    }
    return 0;
}
