/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:35 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/08 13:46:36 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/* parser */

typedef struct s_cmd
{
	char		**argv;
	char		*path;
}				t_cmd;

/// @brief (only in pipex proj) malloc-ed:
/// t_cmd *cmds
typedef struct s_parsed
{
	int			in_fd;
	int			out_fd;
	int			cmd_count;
	int			cmd_start_idx;
	t_cmd		*cmds;
	int			here_doc;
	char		*limiter;
}				t_parsed;

/// @brief (only in pipex proj) malloc-ed:
/// int **pipes
/// pid_t *pids
/// t_parsed *parsed
typedef struct s_parent
{
	t_parsed	*parsed;
	int			**pipes;
	pid_t		*pids;
	int			spawned;
}				t_parent;

/* parser */
int				find_path_idx_envp(char **envp);
void			fetch_cmd_path(char *cmd_name, char **envp, char **path,
					t_parent *parent);
void			parse_cmd(char *cmd_str, t_cmd *cmd, char **envp,
					t_parent *parent);
void			parse_input(int argc, char **argv, char **envp,
					t_parent *parent);
void			get_input_pattern(t_parsed *p, int argc, char **argv,
					t_parent *parent);
void			parse_multi_cmds(t_parsed *p, char **argv, char **envp,
					t_parent *parent);
void			open_input(t_parsed *p, char **argv, t_parent *parent);
void			open_output(t_parsed *p, int argc, char **argv,
					t_parent *parent);
int				here_doc_pipe(char *limiter, t_parent *parent);

/* pipes */
void			setup_pipes(int cmd_count, t_parent *parent);

/* pipeline */
void			connect_stdin(t_parent *parent, int cmd_idx);
void			connect_stdout(t_parent *parent, int cmd_idx);
void			child_exec_command(t_parent *parent, char **envp, int cmd_idx);
pid_t			launch_command(t_parent *parent, int cmd_idx, char **envp);
void			launch_pipeline(t_parent *parent, char **envp);

/* process supervision */
void			close_all_fd_safe(t_parent *parent);
int				parent_wait_and_collect(t_parent *parent);

/* error */
void			fatal_child_syscall(t_parent *parent, char *msg, int exit_code);
void			fatal_parent_prefork(t_parent *parent, char *msg);
void			fatal_parent_postfork(t_parent *parent, const char *msg_where);
void			command_not_found(t_parent *parent, char *cmd);

/* cleanup */
void			cleanup_cmds_then_tparsed(t_parsed *parsed);
void			cleanup_pipes(int **pipes, int pipe_count);
void			cleanup_parent(t_parent *parent);
void			cleanup_child(t_parent *parent);

/* utils */
char			*strjoin_3_safe(char *a, char *b, char *c, t_parent *parent);

#endif
