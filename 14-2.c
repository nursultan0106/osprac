#include <signal.h>
#include <stdio.h>

void myHandler(int nsig) {
  if(nsig == SIGINT) {
    printf("CTRL + С pressed");
  }
  else if(nsig == SIGQUIT) {
    printf("CTRL + 4 pressed");
  }
}

int main(void) {
  signal(SIGINT, myHandler);
  signal(SIGQUIT, myHandler);

  while(1);
  return 0;
}
