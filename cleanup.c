/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:10 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/08 13:46:11 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief
/// @param parsed
void	cleanup_cmds_then_tparsed(t_parsed *parsed)
{
	int	i;

	if (!parsed)
		return ;
	if (parsed->cmds)
	{
		i = 0;
		while (i < parsed->cmd_count)
		{
			if (parsed->cmds[i].argv)
				ft_free_split(parsed->cmds[i].argv);
			if (parsed->cmds[i].path)
				free(parsed->cmds[i].path);
			i++;
		}
		free(parsed->cmds);
	}
	free(parsed);
}

void	cleanup_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

/// @brief cleanup all malloc'd memory in parent struct
/// @param parent
void	cleanup_parent(t_parent *parent)
{
	int	pipe_count;

	if (!parent)
		return ;
	pipe_count = 0;
	if (parent->parsed)
		pipe_count = parent->parsed->cmd_count - 1;
	cleanup_cmds_then_tparsed(parent->parsed);
	parent->parsed = NULL;
	cleanup_pipes(parent->pipes, pipe_count);
	if (parent->pids)
		free(parent->pids);
}

void	cleanup_child(t_parent *parent)
{
	int	pipe_count;

	if (!parent)
		return ;
	pipe_count = 0;
	if (parent->parsed)
		pipe_count = parent->parsed->cmd_count - 1;
	cleanup_cmds_then_tparsed(parent->parsed);
	cleanup_pipes(parent->pipes, pipe_count);
	if (parent->pids)
		free(parent->pids);
}
