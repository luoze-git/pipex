# include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_parsed* argv_parsed;
    pid_t p1;
    pid_t p2;
    int pipefd[2];
    int status1;
    int status2;
    
    argv_parsed = parse_she_line(argc, argv);
    if( pipe(pipefd) == -1)
        error_exit();
    p1 = fork();
    if (p1 == -1)
        error_exit();
    if (p1 == 0)
    {
        child1_producer_run(argv_parsed->in_fd, pipefd);
        exec_cmd(argv_parsed->cmd1_path, argv_parsed->cmd1_argv, envp);
        return 1;
    }
    else
    {
        p2 = fork();
        if (p2 == -1)
            error_exit();

        if (p2 == 0)
        {
            child2_consumer_run(argv_parsed->out_fd, pipefd);
            exec_cmd(argv_parsed->cmd2_path, argv_parsed->cmd2_argv, envp);
            return 1;
        }
        else
        {
            parent_seal(argv_parsed->in_fd,argv_parsed->out_fd ,pipefd);
        }
    }

    // here is only reached by parent
    waitpid(p1,&status1,0 );
    waitpid(p2,&status2,0 );

    if (WIFEXITED(status2))
        return (WEXITSTATUS(status2));
    return 1;
}
