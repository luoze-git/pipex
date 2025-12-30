#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_parsed	*parsed;
	t_parent	parent;
	int			exit_code;

	parsed = parse_input(argc, argv, envp);//todo guard
	parent.parsed = parsed;
	parent.pipes = setup_pipes(parsed->cmd_count);
	parent.pids = NULL;
	launch_pipeline(&parent, envp); // todo check error before running execve for children
	close_all_fd(&parent);
	exit_code = parent_wait_and_collect(&parent);
	cleanup_parent(&parent);//todo
	return (exit_code);
}
