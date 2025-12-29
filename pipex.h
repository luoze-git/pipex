#ifndef PIPEX_H
#define PIPEX_H

#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

void error_exit(void);

typedef struct s_parsed
{
	int in_fd;
	int out_fd;
	char *cmd1_path;
	char **cmd1_argv;
	char *cmd2_path;
	char **cmd2_argv;
} t_parsed;

/* parser */
t_parsed *parse_she_line(int argc, char **argv, char **envp);

/* topology */
void child1_producer_run(int in_fd, int pipefd[2]);
void child2_consumer_run(int out_fd, int pipefd[2]);
void parent_seal(int in_fd, int out_fd, int pipefd[2]);

/* exec */
void exec_cmd(char *cmd_path, char **cmd_argv, char **envp);

#endif
