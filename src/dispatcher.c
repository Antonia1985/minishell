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
    int status;
    int i = 0;
    int redir_type;

	redir_type = redirection_type(cmd);
    while (g_builtins[i].name != NULL)
    {
        if (ft_strcmp(cmd->argv[0], g_builtins[i].name) == 0)
        {           
            if(redir_type == 1)
			redirect_fd(cmd->infile, 1);
            if(redir_type == 2)
                redirect_fd(cmd->outfile, 2);
            if(redir_type == 3)
                redirect_fd(cmd->outfile, 3);
            status = g_builtins[i].func(cmd->argv, &state->env_list, state);
            g_exit_status = status;
            return status;
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
-Involved with redirection (e.g. >, <, >>)
*/