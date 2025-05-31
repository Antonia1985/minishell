#include "minishell.h"
#include "libft.h"

static t_builtin g_builtins[] = {
    {"cd", ft_cd, 1},
    {"exit", ft_exit, 1},
    {"export", ft_export, 1},
    {"unset", ft_unset, 1},
    {"echo", ft_echo, 0},
    {"pwd", ft_pwd, 0},   
    {"env", ft_env, 0},
    {NULL, NULL, 0}
};

int is_builtin(char *command)
{
    int i = 0;
    while (g_builtins[i].name != NULL)
    {
        if (ft_strcmp(command, g_builtins[i].name) == 0)
            return (1);
        i++;
    }
    return (0);
}

int execute_builtin(char **cmd_argv, t_shell_state *state)
{
    int status;
    int i = 0;
    //envp = &state->mini_envp;
    while (g_builtins[i].name != NULL)
    {
        if (ft_strcmp(cmd_argv[0], g_builtins[i].name) == 0)
        {
            status = g_builtins[i].func(cmd_argv, &state->mini_envp, state);
            g_exit_status = status;
            return status;
        }
        i++;
    }   
    return(0);
}
