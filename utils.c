#include "pipex.h"

int    isfailed(t_err error, char *msg)
{
    if (error == syscall_fail)
    {
        perror(msg);
        return (1);
    }
    else if (error == malloc_fail)
    {
        ft_putendl_fd(msg, 2);
        return (1);
    }
    return (0);
}


void	free_2darr(char **ptr)
{
	char	**tmp;

	tmp = ptr;
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(tmp);
}

void    free_cmds(t_cmd **cmd, int i)
{
    while (i--)
    {
        free((*(cmd + i))->fullpath);
        (*(cmd + i))->fullpath = NULL;
        free_2darr((*(cmd + i))->args);
        free(*(cmd + i));
        *(cmd + i) = NULL;
    }
    free(cmd);
    cmd = NULL;
}