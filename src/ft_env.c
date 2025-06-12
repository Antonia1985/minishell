#include "minishell.h"
#include "libft.h"

int ft_env(char **cmd_argv, t_env **env_list, t_shell_state *state)
{
    (void)cmd_argv;
    (void)state;
    char **envp;
    int i;

    envp = env_list_to_envp(*env_list, state);
    i = 0;
    if (!envp)
        return (1);
    while( (envp)[i] != NULL)
    {
        printf("%s\n", (envp)[i]);
        i++;
    }
    free_array(envp);
    return(0);
}