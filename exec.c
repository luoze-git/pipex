# include "pipex.h"


void	exec_cmd(char *cmd_path, char **cmd_argv, char **envp)
{
	execve(cmd_path, cmd_argv, envp);
	error_exit();
}
