#include "pipex.h"

static void	init_parent(t_parent *parent)
{
	parent->parsed = NULL;
	parent->pipes = NULL;
	parent->pids = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_parent	parent;
	int			exit_code;

	init_parent(&parent);
	parse_input(argc, argv, envp, &parent);
	setup_pipes(parent.parsed->cmd_count, &parent);
	launch_pipeline(&parent, envp);
	close_all_fd_safe(&parent);
	exit_code = parent_wait_and_collect(&parent);
	cleanup_parent(&parent);
	return (exit_code);
}
