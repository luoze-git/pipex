#include "pipex.h"

void fatal_error_child(const char *where)
{
	perror(where);
	exit(1);
}



void child1_producer_run(t_parsed *parsed, char **envp, int pipefd[2])
{
	if (dup2(parsed->in_fd, STDIN_FILENO) == -1)
		fatal_error_child("dup2");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		fatal_error_child("dup2");

	close(parsed->in_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(parsed->cmd1_path, parsed->cmd1_argv, envp);
	fatal_error_child("execve");
}

void child2_consumer_run(t_parsed *parsed, char **envp, int pipefd[2])
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		fatal_error_child("dup2");
	if (dup2(parsed->out_fd, STDOUT_FILENO) == -1)
		fatal_error_child("dup2");

	close(parsed->out_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(parsed->cmd2_path, parsed->cmd2_argv, envp);

	fatal_error_child("execve");
}

void parent_seal(int in_fd, int out_fd, int pipefd[2])
{
	close(in_fd);
	close(out_fd);
	close(pipefd[0]);
	close(pipefd[1]);
}
