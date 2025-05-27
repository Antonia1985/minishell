#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>// for LLONG_MAX

typedef int(*buildin_func)(char **);

typedef struct s_builtin{
    char    *name;
    buildin_func func;
}t_builtin;

extern int  g_exit_status;

int     main(int argc, char **argv, char **envp);
int     execute(char **cmd_argv, char **envp, char *full_path, char **path_list);
int     execute_builtin(char **cmd_argv);
int     is_builtin(char *command);
int	    exists_in_path(char *command);
char 	**get_path_list(void);
char	*get_full_path(char *command, char **path_list);
int     ft_cd(char **cmd_argv);
int     ft_exit(char **cmd_argv);
int     ft_echo(char **cmd_argv);
void	free_array(char **path_list);

#endif
