#include "pipex.h"


void fatal_error_parent(t_parsed *parsed, const char *where, pid_t p1 , int pipefd[2])
{
	perror(where);
    parent_seal(parsed->in_fd, parsed->out_fd, pipefd);
    waitpid(p1, NULL, 0);
	exit(1);
}

int main(int argc, char **argv, char **envp)
{
    t_parsed *argv_parsed;
    pid_t p1;
    pid_t p2;
    int pipefd[2];
    int status1;
    int status2;

    argv_parsed = parse_she_line(argc, argv, envp);
    if (pipe(pipefd) == -1)
        error_exit();
    p1 = fork();
    if (p1 == -1)
        exit(1);
    if (p1 == 0)
    {
        child1_producer_run(argv_parsed->in_fd, pipefd);
    }
    else
    {
        p2 = fork();
        if (p2 == -1)
            fatal_error_parent(argv_parsed, "fork", p1, pipefd );

        if (p2 == 0)
        {
            child2_consumer_run(argv_parsed->out_fd, pipefd);
        }
        else
        {
            parent_seal(argv_parsed->in_fd, argv_parsed->out_fd, pipefd);

            waitpid(p1, &status1, 0);
            waitpid(p2, &status2, 0);

            if (WIFEXITED(status2))
                return (WEXITSTATUS(status2));
        }
    }

    return 1;
}
