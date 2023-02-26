#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "libft.h"

typedef struct s_cmd
{
    char    *fullpath;
    char    **args;
}   t_cmd;

typedef struct s_process
{
    pid_t   one;
    pid_t   two;
}   t_process;


# define ROMODE 00444
# define RWMODE 00666
# define FAIL -1
# define ERPATH "pipex: PATH variable not found"
# define ERHEAP "malloc: failed to allocate the required memory"
# define ERINVC "pipex: not a valid command"

t_cmd *get_cmd(const char *cmd_basename, char **paths);