/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:15 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/08 13:46:16 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief used only when a command is not found and exit
/// @param parent
/// @param cmd
void	command_not_found(t_parent *parent, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	close_all_fd_safe(parent);
	cleanup_child(parent);
	exit(127);
}

void	fatal_child_syscall(t_parent *parent, char *msg, int exit_code)
{
	perror(msg);
	close_all_fd_safe(parent);
	cleanup_child(parent);
	exit(exit_code);
}

void	fatal_parent_prefork(t_parent *parent, char *msg)
{
	perror(msg);
	close_all_fd_safe(parent);
	cleanup_parent(parent);
	exit(1);
}

/*Children are waited for only to avoid zombies*/
void	fatal_parent_postfork(t_parent *parent, const char *msg_where)
{
	perror(msg_where);
	close_all_fd_safe(parent);
	parent_wait_and_collect(parent);
	cleanup_parent(parent);
	exit(1);
}
