# include "pipex.h"

/*cleanup only malloc memory*/
void cleanup_cmds(t_parsed *parsed)
{
    int i;

    if (!parsed)
        return;

    if (parsed->cmds)
    {
        i = 0;
        while (i < parsed->cmd_count)
        {
            if (parsed->cmds[i].argv)
                ft_free_split(parsed->cmds[i].argv);
            if (parsed->cmds[i].path)
                free(parsed->cmds[i].path);
            i++;
        }
        free(parsed->cmds);
    }
    free(parsed);
}

void cleanup_pipes(int **pipes, int pipe_count)
{
    int i;

    if (!pipes)
        return;

    i = 0;
    while (i < pipe_count)
    {
        free(pipes[i]);
        i++;
    }
    free(pipes);
}

void cleanup_parent(t_parent *parent)
{
    if (!parent)
        return;

    cleanup_cmds(parent->parsed);
    cleanup_pipes(parent->pipes, parent->parsed->cmd_count - 1);

    if (parent->pids)
        free(parent->pids);
}
