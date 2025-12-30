#ifndef PIPEX_H
#define PIPEX_H

#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

/* parser */

typedef struct s_cmd
{
    char **argv;
    char *path;
} t_cmd;

typedef struct s_parsed
{
    int in_fd;
    int out_fd;
    int cmd_count;
    t_cmd *cmds;
} t_parsed;

typedef struct s_parent
{
    t_parsed *parsed;
    int **pipes;
    pid_t *pids;
} t_parent;

/* parser */
int find_path_idx_envp(char **envp);
void fetch_cmd_path(char *cmd_name, char **envp, char **path);
void parse_cmd(char *cmd_str, t_cmd *cmd, char **envp);
t_parsed *parse_input(int argc, char **argv, char **envp);

/* pipes */
int **setup_pipes(int cmd_count);

/* pipeline */
void connect_stdin(t_parent *parent, int cmd_idx);
void connect_stdout(t_parent *parent, int cmd_idx);
void child_exec_command(t_parent *parent, char **envp, int cmd_idx);
pid_t launch_command(t_parent *parent, int cmd_idx, char **envp);
void launch_pipeline(t_parent *parent, char **envp);

/* process supervision */
void close_all_fd(t_parent *parent);
int parent_wait_and_collect(t_parent *parent);

/* error */
void fatal_child(char *msg);

/* utils */
char *ft_strjoin_3_safe(char *a, char *b, char *c);

#endif
