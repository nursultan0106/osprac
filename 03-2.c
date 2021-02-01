#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
  pid_t pid = fork();

  if (pid == -1) {
    /* ошибка */
    printf("Error on program start\n");
    exit(-1);
  } else if (pid == 0) {
    /* ребенок */
    printf("This one is a child process\n");
  } else {
    /* родитель */
    printf("This one is a parent process\n");
  }
}
