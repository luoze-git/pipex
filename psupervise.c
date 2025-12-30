#include "pipex.h"

void close_all_fd(t_parent *parent)
{
    int i;

    close(parent->parsed->in_fd);
    close(parent->parsed->out_fd);

    i = 0;
    while (i < parent->parsed->cmd_count - 1)
    {
        close(parent->pipes[i][0]);
        close(parent->pipes[i][1]);
        i++;
    }
}

int wait_status_to_exit_code(int status)
{
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    else
        return (1);
}
// read
int parent_wait_and_collect(t_parent *parent)
{
    int i;
    int status;
    int last_exit_code;

    i = 0;
    last_exit_code = 1;
    while (i < parent->parsed->cmd_count)
    {
        waitpid(parent->pids[i], &status, 0);
        if (i == parent->parsed->cmd_count - 1)
            last_exit_code = wait_status_to_exit_code(status);
        i++;
    }
    return (last_exit_code);
}
