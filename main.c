#include "pipex.h"

static void	init_parent(t_parent *parent)
{
	parent->parsed = NULL;
	parent->pipes = NULL;
	parent->pids = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_parsed	*parsed;
	t_parent	parent;
	int			exit_code;

	init_parent(&parent);
	parsed = parse_input(argc, argv, envp);
	parent.parsed = parsed;
	parent.pipes = setup_pipes(parsed->cmd_count);
	parent.pids = NULL;
	launch_pipeline(&parent, envp);
	close_all_fd(&parent);
	exit_code = parent_wait_and_collect(&parent);
	cleanup_parent(&parent);
	return (exit_code);
}
