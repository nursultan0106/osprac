#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid, ppid;
  int a = 0;
  while(a < 7){
    fork();
    a = a+1;
  }
  pid  = getpid();
  ppid = getppid();

  printf("Current pid = %d; current ppid = %d; outcome = %d\n", (int)pid, (int)ppid, a);

  return 0;
}
