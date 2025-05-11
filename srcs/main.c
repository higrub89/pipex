#include "../inc/pipex.h"

int main()
{
    printf("eSTE ES EL NUEVO CAMBIO");

    int file_fd;
    file_fd = open("in.txt", O_RDONLY);
    if (file_fd == -1)
    {
        perror("open");
        return (1);
    }

    if (dup2(file_fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(file_fd);
        return (1);
    }

    char buffer[100];
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        printf("Leído del fichero: %s", buffer);
    }

    close(file_fd);
    return (0);
}