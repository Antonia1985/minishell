#include "minishell.h"
#include "libft.h"

int    ft_cd(char **cmd_argv, char *** envp, t_shell_state *state)
{    
    (void)envp;
    if (!cmd_argv[1])
    {
        char *home = getenv("HOME");
        if(!home || !chdir(home))
        {
            perror("minishell: cd");        
            return(1);
        }
    }
    if (chdir(cmd_argv[1]) != 0)
    {
        char *msg = ft_strjoin("minishell: cd: ", cmd_argv[1]);
        if (!msg)
            malloc_failure(state);
        perror(msg);
        free(msg);
        return(1);
    }        
    return (0);
}