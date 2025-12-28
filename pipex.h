# ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

void	error_exit(void);

/* topology */
void	child1_producer_run(int in_fd, int pipefd[2]);
void	child2_consumer_run(int out_fd, int pipefd[2]);
void	parent_seal(int in_fd, int out_fd, int pipefd[2]);

/* exec */
void	exec_cmd(char *cmd_path, char **cmd_argv, char **envp);


#endif
