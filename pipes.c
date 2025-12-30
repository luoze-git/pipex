
# include "pipex.h"

// pipes number is known from parsed->cmd_count
int **setup_pipes(t_parsed *parsed)
{
    int **pipes;
    int i;

    pipes = malloc(sizeof(int *) * (parsed->cmd_count - 1));
    i = 0;
    while (i < parsed->cmd_count - 1)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1)
            perror("pipe");
        i++;
    }
    return (pipes);
}
