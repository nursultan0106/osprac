#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
printf("Argc = %d", argc);
for(int i = 0; i < argc; i++)
{
printf("The %d element of argv array = ", i);
puts(argv[i]);
printf("\n");
}
for(int i = 0; i < argc; i++)
{
printf("The %d element of envp array = ", i);
puts(envp[i]);
printf("\n");
}
return 0;
}
