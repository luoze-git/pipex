/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:26 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/10 16:37:23 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_path_idx_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*strjoin_3_safe(char *a, char *b, char *c, t_parent *parent)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(a, b);
	if (!tmp1)
		fatal_parent_syscall(parent, "strjoin_3_safe");
	tmp2 = ft_strjoin((const char *)tmp1, c);
	free(tmp1);
	if (!tmp2)
		fatal_parent_syscall(parent, "strjoin_3_safe");
	return (tmp2);
}

/// @brief error handling: irreversible errors are handled by fatal_ and exit.
/// If PATH is not found, *path is set to NULL. (dealt with it before execve)
/// @param cmd_name
/// @param envp
/// @param path
/// @param parent
void	fetch_cmd_path(char *cmd_name, char **envp, char **path,
		t_parent *parent)
{
	int		idx;
	char	**dirs;
	char	*path_candidate;

	*path = NULL;
	idx = find_path_idx_envp(envp);
	if (idx == -1)
		return ;
	dirs = ft_split(envp[idx] + 5, ':');
	if (!dirs)
		fatal_parent_syscall(parent, "split dirs");
	idx = 0;
	while (dirs[idx])
	{
		path_candidate = strjoin_3_safe(dirs[idx], "/", cmd_name, parent);
		if (access(path_candidate, X_OK) == 0)
		{
			*path = path_candidate;
			break ;
		}
		free(path_candidate);
		idx++;
	}
	ft_free_split(dirs);
}

void	parse_cmd(char *cmd_str, t_cmd *cmd, char **envp, t_parent *parent)
{
	if (!cmd_str || cmd_str[0] == '\0')
		fatal_parent_logical_error(parent, "pipex: empty command");
	cmd->argv = ft_split(cmd_str, ' ');
	if (!cmd->argv)
		fatal_parent_syscall(parent, "split cmd argv");
	if (ft_strchr(cmd->argv[0], '/'))
	{
		cmd->path = ft_strdup(cmd->argv[0]);
		if (!cmd->path)
			fatal_parent_syscall(parent, "strdup cmd path");
	}
	else
		fetch_cmd_path(cmd->argv[0], envp, &(cmd->path), parent);
}

void	parse_multi_cmds(t_parsed *p, char **argv, char **envp,
		t_parent *parent)
{
	int	i;

	p->cmds = ft_calloc(p->cmd_count, sizeof(t_cmd));
	if (!p->cmds)
		fatal_parent_syscall(parent, "malloc");
	i = 0;
	while (i < p->cmd_count)
	{
		parse_cmd(argv[p->cmd_start_idx + i], &p->cmds[i], envp, parent);
		i++;
	}
}
