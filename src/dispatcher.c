#include "minishell.h"
#include "libft.h"

static t_builtin g_builtins[] = {
    {"cd", ft_cd},
    {"exit", ft_exit},
    {"echo", ft_echo},
    /*{"pwd", ft_pwd},   
    {"export", ft_export},
    {"unset", ft_unset},
    {"env", ft_env},*/
    {NULL, NULL}
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

int execute_builtin(char **cmd_argv)
{
    int status;
    int i = 0;
    while (g_builtins[i].name != NULL)
    {
        if (ft_strcmp(cmd_argv[0], g_builtins[i].name) == 0)
        {
            status = g_builtins[i].func(cmd_argv);
            g_exit_status = status;
            //return status;
        }
        i++;
    }   
    return(0);
}
