#include "pipex.h"

// name file1 cmd1 cmd2 file2
// 0     1     2    3    4

int find_path_idx_envp(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (i);
        i++;
    }
    return (-1);
}

void fetch_cmd_path(char *cmd_name, char **envp, char **path)
{
    // This function should resolve the command path using the PATH env variable
    int idx = find_path_idx_envp(envp);
    if (idx == -1)
{
    *path = NULL;
    return;
}

    char **dirs = ft_split(envp[idx] + 5, ':');
    char *path_candidate;
    idx = 0;
    while (dirs[idx])
    {
        path_candidate = ft_strjoin_3_safe(dirs[idx], "/", cmd_name);
        if (access(path_candidate, X_OK) == 0)
        {
            *path = path_candidate;
            break;
        }
        free(path_candidate);
        idx++;
    }
    free(dirs);
}

void parse_cmd(char *cmd_str, t_cmd *cmd, char **envp)
{
    cmd = malloc(sizeof(t_cmd));
    cmd->argv = ft_split(cmd_str, ' ');
    // For simplicity, assume the path is just the command name
    if (ft_strchr(cmd->argv[0], '/'))
        cmd->path = ft_strdup(cmd->argv[0]);
    else
        fetch_cmd_path(cmd->argv[0], envp, &(cmd->path));
}

t_parsed *parse_input(int argc, char **argv, char **envp)
{
    t_parsed *parsed;

    parsed = malloc(sizeof(t_parsed));
    if (!parsed)
        return (NULL);
    parsed->in_fd = open(argv[1], O_RDONLY);

    int cmd_i = 0;
    parsed->cmd_count = argc - 3;
    parsed->cmds = malloc(sizeof(t_cmd) * parsed->cmd_count);

    while (cmd_i < argc - 3)
    {
        parse_cmd(argv[cmd_i + 2], &parsed->cmds[cmd_i], envp);
        cmd_i++;
    }
    parsed->out_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    return (parsed);
}
