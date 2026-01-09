/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:38 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/09 20:22:26 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	connect_stdin(t_parent *parent, int cmd_idx)
{
	if (cmd_idx == 0)
	{
		if (dup2(parent->parsed->in_fd, STDIN_FILENO) == -1)
			fatal_child_syscall(parent, "dup2 stdin", 1);
	}
	else
	{
		if (dup2(parent->pipes[cmd_idx - 1][0], STDIN_FILENO) == -1)
			fatal_child_syscall(parent, "dup2 stdin", 1);
	}
}

void	connect_stdout(t_parent *parent, int cmd_idx)
{
	if (cmd_idx == parent->parsed->cmd_count - 1)
	{
		if (dup2(parent->parsed->out_fd, STDOUT_FILENO) == -1)
			fatal_child_syscall(parent, "dup2 stdout", 1);
	}
	else
	{
		if (dup2(parent->pipes[cmd_idx][1], STDOUT_FILENO) == -1)
			fatal_child_syscall(parent, "dup2 stdout", 1);
	}
}

void	child_exec_command(t_parent *parent, char **envp, int cmd_idx)
{
	t_cmd	cmd;

	cmd = parent->parsed->cmds[cmd_idx];
	connect_stdin(parent, cmd_idx);
	connect_stdout(parent, cmd_idx);
	close_all_fd_safe(parent);
	if (cmd.path == NULL)
		command_not_found(parent, cmd.argv[0]);
	execve(cmd.path, cmd.argv, envp);
	fatal_child_syscall(parent, "execve", 1);
}

pid_t	launch_command(t_parent *parent, int cmd_idx, char **envp)
{
	pid_t	pid_cur;

	pid_cur = fork();
	if (pid_cur < 0)
		fatal_parent_postfork_syscall(parent, "fork");
	if (pid_cur == 0)
		child_exec_command(parent, envp, cmd_idx);
	return (pid_cur);
}

void	launch_pipeline(t_parent *parent, char **envp)
{
	int	i;

	parent->spawned = 0;
	parent->pids = malloc(sizeof(pid_t) * parent->parsed->cmd_count);
	if (!parent->pids)
		fatal_parent_syscall(parent, "malloc");
	i = 0;
	while (i < parent->parsed->cmd_count)
	{
		parent->pids[i] = launch_command(parent, i, envp);
		parent->spawned++;
		i++;
	}
}
