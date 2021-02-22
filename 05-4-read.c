#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd, answer;
    size_t size;
    char answer_string[14];
    char name[] = "file.fifo";
    (void)umask(0);

    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
        printf("Can not create FIFO\n");
        exit(-1);
    }
    printf("FIFO is created\n");
    printf("Reading data from fifo\n");

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Can not open FIFO for reading\n");
        exit(-1);
    }
    size = read(fd, answer_string, 14);
    if (size < 0) {
        printf("Can not read string\n");
        exit(-1);
    }
    printf("Answer read from fifo: %s\n", answer_string);
    printf("Reader closing\n");
    close(fd);
    return 0;
}
