#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

int answer = 0;

int main() {
    int arr[2];
    size_t size = 1;
    char* answer_string = malloc(1 * sizeof(char));
    if(pipe(arr) < 0) {
        printf("Can not create pipe\n");
        exit(-1);
    }
    fcntl(arr[1], F_SETFL, fcntl(arr[1], F_GETFL) | O_NONBLOCK);
    
    while (size == 1) {
        size = write(arr[1], answer_string, 1);
        answer++;
    }
    printf("Answer: %d bytes\n", answer);
    return 0;
}
