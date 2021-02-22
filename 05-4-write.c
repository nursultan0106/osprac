#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd, answer; size_t size; char answer_string[14]; char name[]="file.fifo";
    (void)umask(0);
    
    printf("Writting data to fifo\n");
    
    if((fd = open(name, O_WRONLY)) < 0){
        printf("Can not open FIFO for writing\n");
        exit(-1);
    }
    size = write(fd, "Hello, world!", 14);
    printf("Wrote to fifo\n");
    if(size != 14) {
        printf("Can not write all string to FIFO\n");
        exit(-1);
    }
    close(fd);
    printf("Writer closing\n");
    return 0;
}
