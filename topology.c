# include "pipex.h"

void	child1_producer_run(int in_fd, int pipefd[2])
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
		error_exit();
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_exit();

	close(in_fd);
	close(pipefd[0]);
	close(pipefd[1]);

}

void	child2_consumer_run(int out_fd, int pipefd[2])
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_exit();
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		error_exit();

	close(out_fd);
	close(pipefd[0]);
	close(pipefd[1]);

}

void	parent_seal(int in_fd, int out_fd, int pipefd[2])
{
	close(in_fd);
	close(out_fd);
	close(pipefd[0]);
	close(pipefd[1]);
}
