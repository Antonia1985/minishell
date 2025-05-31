#include "minishell.h"
#include "libft.h"

int ft_pwd(char **cmd_argv, char *** envp, t_shell_state *state)
{
    (void)cmd_argv;
    (void)envp;
    (void)state;
    char *cwd = getcwd(NULL, 0);
    
	if (!cwd)
        return (1);
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
