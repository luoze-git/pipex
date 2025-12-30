#include "pipex.h"

void connect_stdin(t_parent *parent, int cmd_idx)
{
    if (cmd_idx == 0)
    {
        if (dup2(parent->parsed->in_fd, STDIN_FILENO) == -1)
            fatal_child("dup2 stdin");
    }
    else
    {
        if (dup2(parent->pipes[cmd_idx - 1][0], STDIN_FILENO) == -1)
            fatal_child("dup2 stdin");
    }
}

void connect_stdout(t_parent *parent, int cmd_idx)
{
    if (cmd_idx == parent->parsed->cmd_count - 1)
    {
        if (dup2(parent->parsed->out_fd, STDOUT_FILENO) == -1)
            fatal_child("dup2 stdout");
    }
    else
    {
        if (dup2(parent->pipes[cmd_idx][1], STDOUT_FILENO) == -1)
            fatal_child("dup2 stdout");
    }
}




void child_exec_command(t_parent *parent, char **envp, int cmd_idx)
{
    t_cmd cmd;

    cmd = parent->parsed->cmds[cmd_idx];

    connect_stdin(parent, cmd_idx);
    connect_stdout(parent, cmd_idx);

    close_all_fd(parent);
    execve(cmd.path, cmd.argv, envp);
    fatal_child("execve");
}


pid_t launch_command(t_parent *parent, int cmd_idx, char **envp )
{
	pid_t pid_cur;
	pid_cur = fork();
	if (pid_cur < 0)
		perror("fork");
	if (pid_cur == 0)
		child_exec_command(
			parent,
			envp,
			cmd_idx
		);
	return (pid_cur);
}


void launch_pipeline(t_parent *parent, char **envp)
{
    int i;

    parent->pids = malloc(sizeof(pid_t) * parent->parsed->cmd_count);
    if (!parent->pids)
        exit(1);
    i = 0;
    while (i < parent->parsed->cmd_count)
    {
        parent->pids[i] = launch_command(parent, i, envp);
        i++;
    }
}


