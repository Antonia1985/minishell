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

int	should_run_in_parent(char *command)
{
	int i = 0;
    while (g_builtins[i].name != NULL)
    {
        if (ft_strcmp(command, g_builtins[i].name) == 0 && g_builtins[i].only_in_parent == 1)
            return (1);
        i++;
    }
    return (0);
}

int execute_builtin(t_command *cmd, t_shell_state *state)
{
    //int status;
    int i = 0;
    int stdout = -1;

    while (g_builtins[i].name != NULL)
    {
        if (ft_strcmp(cmd->argv[0], g_builtins[i].name) == 0)
        {
            if(cmd->has_redirection)
            {
                //printf("entered in: cmd-> has_redirection\n"); //delete it
                stdout = dup(STDOUT_FILENO);
                apply_redirections(cmd);
            }
            //printf("entered in: executing the builtin\n"); //delete it
            g_exit_status = g_builtins[i].func(cmd->argv, &state->env_list, state);

            dup2(stdout, STDOUT_FILENO);
            close (stdout);
            return g_exit_status;
        }
        i++;
    }   
    return(0);
}


/*
Built-ins like echo, pwd, env:
Can run without forking, for performance.

Must fork if they're:
-In a pipeline
*/