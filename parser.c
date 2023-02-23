#include "pipex.h"

// free 2d arr
void    free_double(char **arr)
{
    int i;

    i = 0;
    while (*(arr + i))
    {
        free(*(arr + i));
        i++;
    }
    free(arr);
}
// check for cmd existence and usability
char    *get_exec_path(char *cmd, char **paths)
{
    char    *current;
    char    *valid;
    int     i;

    valid = NULL;
    if (!paths)
        return NULL;
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
char **parse_cmd(const char *cmd)
{
    char **parsed_cmd;
    char *tmp;

    parsed_cmd = ft_split(cmd, ' ');
    tmp = *parsed_cmd;
    *parsed_cmd = ft_strjoin("/", tmp);
    if (!parsed_cmd)
    {
        perror("Erorr");
        exit(EXIT_FAILURE);
    }
    free(tmp);
    return (parsed_cmd);
}

t_pip *get_cmd(const char *cmd_basename, char **paths)
{
    t_pip   *cmd;

    cmd = (t_pip *)malloc(sizeof(t_pip));
    if (!cmd)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    cmd->cmd = parse_cmd(cmd_basename);
    cmd->cmd_fullpath = get_exec_path(cmd->cmd[0], paths);
    if (!cmd->cmd_fullpath)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    return (cmd);
}