
#include "pipex.h"

static void	close_pipe_pair(int *pipefd)
{
	if (!pipefd)
		return ;
	if (pipefd[0] >= 0)
	{
		close(pipefd[0]);
		pipefd[0] = -1;
	}
	if (pipefd[1] >= 0)
	{
		close(pipefd[1]);
		pipefd[1] = -1;
	}
}

/// @brief close all fds from t_parent struct and set them to
	-1. Check before closing to avoid closing invalid fds.
/// @param parent
void	close_all_fd_safe(t_parent *parent)
{
	int	i;
	int	pipe_count;

	if (!parent || !parent->parsed)
		return ;
	if (parent->parsed->in_fd >= 0)
	{
		close(parent->parsed->in_fd);
		parent->parsed->in_fd = -1;
	}
	if (parent->parsed->out_fd >= 0)
	{
		close(parent->parsed->out_fd);
		parent->parsed->out_fd = -1;
	}
	if (!parent->pipes)
		return ;
	pipe_count = parent->parsed->cmd_count - 1;
	i = 0;
	while (i < pipe_count)
	{
		close_pipe_pair(parent->pipes[i]);
		i++;
	}
}
