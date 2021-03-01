#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    int *array;
    int shmid;
    char pathname[] = "07-1a.c";
    key_t key;
    char *sourceCode;
    
    int fileSize = 0;
    int *file_size_ptr;
    
    if ((key = ftok(pathname,0)) < 0) {
        printf("Can not generate key\n");
        exit(-1);
    }
    
    if ((shmid = shmget(key, sizeof(int) + fileSize * sizeof(char), 0)) < 0) {
        printf("Can not create shared memory\n");
        exit(-1);
    }

    if ((file_size_ptr = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Can not attach shared memory\n");
        exit(-1);
    }

    fileSize = *file_size_ptr;
    sourceCode = (char*)(file_size_ptr + 1);
    
    for (int i = 0; i < fileSize; i++)
        putchar(sourceCode[i]);
    
    if (shmdt(file_size_ptr) < 0) {
        printf("Can not detach shared memory\n");
        exit(-1);
    }
    
    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        printf("Can not delete shared memory\n");
        exit(-1);
    }
    return 0;
}
