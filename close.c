/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:13 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/10 15:36:52 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pipe_pair(int *pipefd)
{
	if (!pipefd)
		return ;
	if (pipefd[0] >= 0)
	{
		close(pipefd[0]);
		pipefd[0] = -1;
	}
	if (pipefd[1] >= 0)
	{
		close(pipefd[1]);
		pipefd[1] = -1;
	}
}

/// @brief close all fds from t_parent struct and set them to
///	-1. Check before closing to avoid closing invalid fds.
/// @param parent
void	close_all_fd_safe(t_parent *parent)
{
	int	i;
	int	pipe_count;

	if (!parent || !parent->parsed)
		return ;
	if (parent->parsed->infile_fd >= 0)
	{
		close(parent->parsed->infile_fd);
		parent->parsed->infile_fd = -1;
	}
	if (parent->parsed->outfile_fd >= 0)
	{
		close(parent->parsed->outfile_fd);
		parent->parsed->outfile_fd = -1;
	}
	if (!parent->pipes)
		return ;
	pipe_count = parent->parsed->cmd_count - 1;
	i = 0;
	while (i < pipe_count)
	{
		close_pipe_pair(parent->pipes[i]);
		i++;
	}
}
