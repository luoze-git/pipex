# include "pipex.h"

int pipefd[2];

// pipe and guard the failure
if (pipe(pipefd) == -1)
    error_exit();

    // process 
pid_t pid1;
pid_t pid2;

// gen process and guard the failure
pid1 = fork();
if (pid1 == -1)
    error_exit();

if (pid1 == 0)
{
}
else 
{
    pid2 = fork();
    if (pid2 == -1)
        error_exit();

    if (pid2 == 0)
    {

    }
    else
    {

    }
}


static void	child1_producer_run(int in_fd, int pipefd[2])
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
		error_exit();
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_exit();

	close(in_fd);
	close(pipefd[0]);
	close(pipefd[1]);

}

static void	child2_consumer_run(int out_fd, int pipefd[2])
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_exit();
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		error_exit();

	close(out_fd);
	close(pipefd[0]);
	close(pipefd[1]);

}

static void	parent_seal(int in_fd, int out_fd, int pipefd[2])
{
	close(in_fd);
	close(out_fd);
	close(pipefd[0]);
	close(pipefd[1]);
}

execve(cmd1_path, cmd1_argv, envp);
error_exit(); /* execve only returns on failure */


execve(cmd2_path, cmd2_argv, envp);
error_exit(); /* execve only returns on failure */


int status1;
int status2;

waitpid(pid1, &status1, 0);
waitpid(pid2, &status2, 0);

if (WIFEXITED(status2))
    return WEXITSTATUS(status2);
return 1;
