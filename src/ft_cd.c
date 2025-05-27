#include "minishell.h"
#include "libft.h"

int    ft_cd(char **cmd_argv)
{    
    //char *oldpwd = getcwd(NULL, 0);
   
    //printf("Trying to cd into: '%s'\n", cmd_argv[1]);
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
        perror(msg);
        free(msg);
        return(1);
    }        
    return (0);
}