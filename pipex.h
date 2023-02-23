#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>

typedef struct s_pipex
{
    char    *cmd_fullpath;
    char    **cmd;
} t_pip;

void    redirect(const char *file, char option);
t_pip *get_cmd(const char *cmd_basename, char **paths);