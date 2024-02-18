#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int input_fd;

    input_fd = open("input.txt", O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(input_fd);

    if (execlp("./new_process", "./new_process", NULL) == -1) {
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0; // This code will not be reached if execlp is successful
}
