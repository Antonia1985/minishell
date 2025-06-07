#include "minishell.h"
#include "libft.h"

void    search_for_key_and_remove(char *key, t_env **env_list)
{
    t_env *current = *env_list;
    t_env *prev = NULL;

    if(current && ft_strcmp(key, current->key) == 0)
    {
        *env_list = current->next;
        free(current);
        return;            
    }
    while(current && ft_strcmp(key, current->key) != 0)
    {
        prev = current;
        current = current->next;
    }
    if(current && ft_strcmp(key, current->key) == 0)
    {
        prev->next = current->next;
        free(current);
    }
}

int ft_unset(char **cmd_argv, t_env **env_list, t_shell_state *state)
{
    (void)state;
    int i;
   
    i = 0;
    while (cmd_argv[i])
        i++;
    if(i <= 1)
    {
        g_exit_status = 0;
        return (g_exit_status);
    }

    i = 1;
    while(cmd_argv[i])
    {
        if (ft_strchr(cmd_argv[i], '=') == NULL)
        {
            search_for_key_and_remove(cmd_argv[i], env_list);
        }
        i++;        
    }
    return(0);
}