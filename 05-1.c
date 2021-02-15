#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd;
    size_t size;

    (void)umask(0);
    printf("Start of the program\n");
    if ((fd = open("myfile", O_RDONLY)) < 0) {
        printf("Can not open the file\n");
        exit(-1);
    }

    char string[14];
    size = read(fd, string, 14);
    if (size != 14) {
        printf("Can not read all strings\n");
        exit(-1);
    }
    
    printf("File: %s\n", string);

    if (close(fd) < 0)
        printf("Can not close the file\n");
    return 0;
}
