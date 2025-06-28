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
    int stdin = -1;
    while (g_builtins[i].name != NULL)
    {
        if (ft_strcmp(cmd->argv[0], g_builtins[i].name) == 0)
        {
            if(cmd->has_redirection)
            {
                //printf("entered in: cmd-> has_redirection\n"); //delete it
                if(!cmd->has_pipe)
                {
                    stdout = dup(STDOUT_FILENO);
                    stdin = dup(STDIN_FILENO);
                    if (stdout == -1 || stdin == -1)
                    {
                        perror("minishell: dup");
                        g_exit_status = 1;
                        return g_exit_status;
                    }
                }                
                if (!apply_redirections(cmd, state))
                {
                    if (!cmd->has_pipe)
                    {
                        if (stdout != -1)
                            close(stdout);
                        if (stdin != -1)
                            close(stdin);
                    }
                    g_exit_status = 1;
                    return (g_exit_status); // Redirection failed; abort builtin
                }
            }
            //printf("entered in: executing the builtin\n"); //delete it
            g_exit_status = g_builtins[i].func(cmd->argv, &state->env_list, state);

            if(!cmd->has_pipe)
            {
                if (stdout != -1)
                {
                    dup2(stdout, STDOUT_FILENO);
                    close (stdout);
                }
                if (stdin != -1)
                {
                    dup2(stdin, STDIN_FILENO);
                    close (stdin);
                }
            }
            return g_exit_status;
        }
        i++;
    }
    print_warning_set_status("minishell: internal error: unknown builtin: %s\n", 
                            (char *[]){cmd->argv[0], NULL}, 1);
    g_exit_status = 1;
    return g_exit_status;
}


/*
Built-ins like echo, pwd, env:
Can run without forking, for performance.

Must fork if they're:
-In a pipeline
*/