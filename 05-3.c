#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/* Реализация синхронизации:
Семафор инициализируется как 1 в начале
Родительский процесс: До цикла D(S,1), затем запись > A(S,1) > Z > D(S,1) > чтение
Ребенок в цикле: D(S,2) > чтение > запись > A(S,1)
*/

int main()
{
    int fd[2], result;
    int counter;
    key_t key;
    int semid;
    struct sembuf mybuf;
    char pathname[] = "05-3.c";
    size_t size;
    char resstring[15];

    printf("Enter the number:");
    scanf("%d", &counter);

    if (pipe(fd) < 0) {
        printf("Can not open pipe\n");
        exit(-1);
    }

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Impossible to generate the key.\n");
        exit(-2);
    }

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Error: Impossible to create the semaphore.\n");
        exit(-3);
    }

    mybuf.sem_num = 0;
    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;

    if (semop(semid, &mybuf, 1) < 0) {
        printf("Can not set initial semaphore value as 1.\n");
        exit(-6);
    }

    result = fork();

    if (result < 0) {
        printf("Can not fork the child. Terminating.\n");
        exit(-5);
    }
    else if (result > 0) {
	mybuf.sem_num = 0;
        mybuf.sem_op = -1;
        mybuf.sem_flg = 0;

        if (semop(semid, &mybuf, 1) < 0) {
            printf("Can not decrease semaphore value by 1.\n");
            exit(-6);
        }

        for (int i = 0; i < counter; ++i) {
            size = write(fd[1], "Hello, child!", 14);

            if (size != 14) {
                printf("Parent: Unable to write all the chars to the pipe.\n");
                exit(-1);
            }

            mybuf.sem_num = 0;
            mybuf.sem_op = 2;
            mybuf.sem_flg = 0;

            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can not enter the critical section properly in program A.\n");
                exit(-6);
            }
            mybuf.sem_num = 0;
            mybuf.sem_op = 0;
            mybuf.sem_flg = 0;
	    
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can not enter the critical section properly in program A.\n");
                exit(-6);
            }
	    
	        mybuf.sem_num = 0;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;

            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can not enter the critical section properly in program A.\n");
                exit(-6);
            }

            size = read(fd[0], resstring, 15);

            if (size < 0) {
                printf("Can not read string from pipe\n");
                exit(-1);
            }

            printf("Parent: Read the string: %s\n", resstring);
        }


        printf("Parent has finished job.\n");

    }
    else {
        for (int i = 0; i < counter; ++i) {
            mybuf.sem_num = 0;
            mybuf.sem_op = -2;
            mybuf.sem_flg = 0;

            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can not enter the critical section properly.\n");
                exit(-6);
            }

            size = read(fd[0], resstring, 14);

            if (size < 0) {
                printf("Child: Impossible to read the string from the pipe.\n");
                exit(-1);
            }

            printf("Child: read the string: %s\n", resstring);
	    
            size = write(fd[1], "Hello, parent!", 15);
	    
            if (size != 15) {
                printf("Child: unable to write all the chars to the pipe.\n");
                exit(-1);
            }    

            mybuf.sem_num = 0;
            mybuf.sem_op = 1;
            mybuf.sem_flg = 0;

            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can not enter the critical section properly.\n");
                exit(-6);
            }
        }
        if (close(fd[0]) < 0) {
            printf("Child: Can not close reading side of pipe\n"); 
            exit(-1);
        }
        if (close(fd[1]) < 0) {
            printf("Child: Can not close writing side of pipe\n"); 
            exit(-1);
        }
    }

    return 0;
}
