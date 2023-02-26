#include "pipex.h"

// check if givin cmd is valid (exist, executable)
static char    *get_exec_path(char *cmd, char **paths)
{
    char    *current;
    char    *valid;
    int     i;

    valid = NULL;
    i = 0;
    while (*(paths + i))
    {
        current = ft_strjoin(*(paths + i), cmd);
        if (current && access(current, F_OK | X_OK) == 0)
        {
            valid = current;
            break ;
        }
        free(current);
        i++;
    }
    return (valid);
}
// prepare cmd and it args
static char **parse_cmd(const char *cmd)
{
    char **parsed_cmd;
    char *tmp;

    parsed_cmd = ft_split(cmd, ' ');
    tmp = *parsed_cmd;
    *parsed_cmd = ft_strjoin("/", tmp);
    if (!parsed_cmd)
    {
        perror(ERHEAP);
        exit(EXIT_FAILURE);
    }
    free(tmp);
    return (parsed_cmd);
}

t_cmd *get_cmd(const char *cmd_basename, char **paths)
{
    t_cmd   *cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
    {
        ft_putendl_fd(ERHEAP, 2);
        exit(EXIT_FAILURE);
    }
    cmd->args = parse_cmd(cmd_basename);
    cmd->fullpath = get_exec_path(cmd->args[0], paths);
    if (!cmd->fullpath)
    {
        ft_putendl_fd(ERINVC, 2);
        ft_putendl_fd((char *)cmd_basename, 2);
        exit(EXIT_FAILURE);
    }
    return (cmd);
}