#define _POSIX_C_SOURCE 200112L
#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>// for LLONG_MAX
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <asm-generic/signal-defs.h>


typedef struct s_env{
    char *key;
    char *value;
    struct s_env *next;
}t_env;

typedef struct s_shell_state{
    char *input;
    char **cmd_argv;
    char *full_path;
    char **path_list;
    char **mini_envp;
    t_env   *env_list;
} t_shell_state;

typedef int(*buildin_func)(char **, t_env **, t_shell_state *);

typedef struct s_builtin{
    char    *name;
    buildin_func func;
    int     only_in_parent;
}t_builtin;

extern int  g_exit_status;

int		main(int argc, char **argv, char **envp);
int		execute(char **cmd_argv, char *full_path, t_shell_state *state);
int		execute_builtin(char **cmd_argv, t_shell_state *state);
int		is_builtin(char *command);
int		exists_in_path(char *command, t_shell_state *state);
char	**get_path_list(t_shell_state *state);
char	*get_full_path(char *command, char **path_list, t_shell_state *state);

//builtins
int		ft_cd(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_exit(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_echo(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_pwd(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_env(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_export(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_unset(char **cmd_argv, t_env **env_list, t_shell_state *state);
void	free_array(char **path_list);
char	*get_env_value(char **envp, char *key_equal, t_shell_state *state);

// shared_fun
void	clean_up_all(t_shell_state *state, int free_env);
void	malloc_failure(t_shell_state *state);
void	exit_with_status(int status, t_shell_state *state);
int		already_exists(char **envp, char *input, int input_len);
int		contains_equal_sign(char *input);
void	free_list(t_env *list);

//converter
t_env *env_list_from_envp(char **envp, t_shell_state *state, int for_envp);
char **env_list_to_envp(t_env *list, t_shell_state *state);


//signals
void    signals_handler(void);
#endif
