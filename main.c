/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:18 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/10 16:34:27 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_parent	parent;
	int			exit_code;

	ft_bzero(&parent, sizeof(t_parent));
	parse_input(argc, argv, envp, &parent);
	setup_pipes(parent.parsed->cmd_count, &parent);
	launch_pipeline(&parent, envp);
	close_all_fd_safe(&parent);
	exit_code = parent_wait_and_collect(&parent);
	cleanup_parent(&parent);
	return (exit_code);
}
