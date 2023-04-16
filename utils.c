#include "pipex.h"

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

# define SE_SUCCESS
# define SE_FAILURE
# define SE_MEMFREE
# define SE_FDCLOSE

void    safe_exit(int status, t_pipex *pipex, int fd[2])
{
    free_cmds(pipex->cmd, pipex->cmd_count);
    free(pipex);
    if (fd)
    {
        close(fd[0]);
        close(fd[1]);
    }
    exit(status);
}
