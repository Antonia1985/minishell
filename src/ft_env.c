#include "minishell.h"
#include "libft.h"

int ft_env(char **cmd_argv, char *** envp, t_shell_state *state)
{
    (void)cmd_argv;
    (void)state;
    int i;

    i = 0;
    if (!*envp)
        return (1);
    while( (*envp)[i] != NULL)
    {
        printf("%s\n", (*envp)[i]);
        i++;
    }
    return(0);
}