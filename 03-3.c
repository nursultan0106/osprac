#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[])
{
    printf("Arguments of the command line:\n");
    for (int i = 0; i < argc; ++i)
        printf("%s\n", argv[i]);
    printf("\n");

    printf("Parametres of the environment:\n");
    int i = 0;
    while (envp[i] != NULL)
        printf("%s\n", envp[i++]);
    printf("\n");

    return 0;
}
