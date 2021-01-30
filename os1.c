#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
printf ("Current User ID = %d\n", getuid());
printf ("Current Group ID = %d\n", getgid());
return 0;
}
