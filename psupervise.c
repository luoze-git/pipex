#include "pipex.h"

void	close_all_fd(t_parent *parent)
{
	int	i;

	if (!parent || !parent->parsed)
		return ;
	if (parent->parsed->in_fd >= 0)
		close(parent->parsed->in_fd);
	if (parent->parsed->out_fd >= 0)
		close(parent->parsed->out_fd);
	i = 0;
	if (!parent->pipes)
		return ;
	while (i < parent->parsed->cmd_count - 1)
	{
		if (parent->pipes[i])
		{
			if (parent->pipes[i][0] >= 0)
				close(parent->pipes[i][0]);
			if (parent->pipes[i][1] >= 0)
				close(parent->pipes[i][1]);
		}
		i++;
	}
}

int	wait_status_to_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

int	parent_wait_and_collect(t_parent *parent)
{
	int	i;
	int	status;
	int	last_exit_code;

	i = 0;
	last_exit_code = 1;
	while (i < parent->spawned)
	{
		waitpid(parent->pids[i], &status, 0);
		if (i == parent->spawned - 1)
			last_exit_code = wait_status_to_exit_code(status);
		i++;
	}
	return (last_exit_code);
}
