#include "minishell.h"
#include "libft.h"

void    delete_var(char***envp, char *key_equal, int key_equ_len, t_shell_state *state)
{
    int i;
    int j;
    int env_len;

    env_len = 0;
    i = 0;
    j = 0;

    //find the length of envp, how many key-values contains i.e. env_len = 10 lines
    while((*envp)[env_len])
        env_len++;

    //create new envp smaller by 1 pair key-value
    char **new_envp = malloc(sizeof(char*)*(env_len)); //env_len = 10 lines -1(for the deleted) + 1 (for NULL) = 10
    if(!new_envp)
        malloc_failure(state);

    //assigne to the new_envp all the pointers of the lines key-value.
    while((*envp)[j])
    {
        if (ft_strncmp((*envp)[j], key_equal, key_equ_len) != 0)// find the envp
        {
            new_envp[i] = ft_strdup((*envp)[j]);
            if (!new_envp[i])
                malloc_failure(state);
            i++;
        }
        j++;
    }
    new_envp[i] = NULL;
    free_array(*envp);
    *envp = new_envp;
}

int ft_unset(char **cmd_argv, char ***envp, t_shell_state *state)
{
    char **input;
    char *key_equal;
    int i;
    int j;
    int key_equ_len;
    int count;

    if (cmd_argv[1])
    {
        count =0;
        i = 1;
        while(cmd_argv[i])
        {
            if(!contains_equal_sign(cmd_argv[i]))
                count++;
            i++;
        }

        input = malloc(sizeof(char *) * (count + 1));
        if (!input)
            malloc_failure(state);

        i = 1;
        j = 0;
        while(cmd_argv[i])
        {
            if(!contains_equal_sign(cmd_argv[i]))
            {
                input[j] = ft_strdup(cmd_argv[i]);
                if(!input[j])
                    malloc_failure(state);
                j++;
            }
            i++;          
        }       
        input[j] = NULL;
        i = 0;
        while(input[i])
        {
            key_equal = ft_strjoin(input[i], "=");
            if(!key_equal)
            {
                free_array(input);
                //free(input);
                malloc_failure(state);
            }

            key_equ_len = ft_strlen(key_equal);
            if (already_exists((*envp), key_equal, key_equ_len))
                delete_var(envp, key_equal, key_equ_len, state);
            free(key_equal);
            i++;
        }
        free_array(input);
        //free(input);
    }
    return(0);
}