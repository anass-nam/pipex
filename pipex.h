#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include "libft.h"

typedef struct s_cmd
{
	char    *fullpath;
	char    **args;
}   t_cmd;

typedef struct	s_pipex
{
	t_cmd	**cmd;
	int		infile;
	int		outfile;
}	t_pipex;


typedef enum    e_err
{
	syscall_fail = -1,
	malloc_fail = 1
}               t_err;

# define FAIL -1
# define ERENV "pipex: cannot access Environment variables"
# define ERPATH "pipex: PATH variable not found"
# define ERHEAP "malloc: Failed to allocate the required memory"
# define ERINVC "\" command not found"

char	**get_env_path(char const **env);
//	utils
int		isfailed(t_err error, char *msg);
void	free_2darr(char **ptr);
void    free_cmds(t_cmd **cmd, int i);