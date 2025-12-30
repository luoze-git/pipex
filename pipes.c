
# include "pipex.h"


int **setup_pipes(int cmd_count)
{
    int **pipes;
    int i;

    pipes = malloc(sizeof(int *) * (cmd_count - 1));
    i = 0;
    while (i < cmd_count - 1)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1)
            perror("pipe");
        i++;
    }
    return (pipes);
}
