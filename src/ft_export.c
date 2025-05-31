#include "minishell.h"
#include "libft.h"

void add_envp(char ***envp, char *input, t_shell_state *state)
{
    int env_len = 0;
    int i = 0;

    //find the length of envp, how many key-values contains
    while((*envp)[env_len])
        env_len++;

    //create new envp to fit the new key-value 
    char **new_envp = malloc(sizeof(char*)*(env_len + 2));
    if(!new_envp)
        malloc_failure(state);

    //assigne to the new_envp all the pointers of the lines key-value.
    while(i < env_len)
    {
        new_envp[i] = ft_strdup((*envp)[i]); // safer: make copies instead of reusing old pointers
        if (!new_envp[i])
            malloc_failure(state);
        i++;
    }

    //at the end of new_envp add the new line
    new_envp[env_len] =  ft_strdup(input);
    if (!new_envp[env_len])
        malloc_failure(state);

    new_envp[env_len+1] = NULL;
   
   // Free old envp
    free_array(*envp);

    // Update original pointer
    (*envp) = new_envp;
}

void    extract_key_and_value(char *input, int input_len, char **key, char **value, t_shell_state *state)
{
    char    *seperator;
    int     seper_len;    
    int     key_len;

    seperator = ft_strchr(input, '=');
    seper_len = ft_strlen(seperator);
    key_len = input_len - seper_len;
    *key = ft_substr(input, 0, key_len);
    if (!*key)
        malloc_failure(state);
    if(!seper_len)
    {
        *value = ft_strdup("");
    }
    else
    {
        *value = ft_substr(input, key_len+1, input_len);
    }    
    if (!*value)
        malloc_failure(state);
}

char    *get_env_value(char **envp, char *key_equal, t_shell_state *state)
{
    char *value_env;
    int i = 0;
    int key_equal_len = ft_strlen(key_equal);
    while(envp[i])
    {
        if(ft_strnstr((const char *)envp[i], (const char *)key_equal, key_equal_len) != NULL)// search in envp[i] for an occurence of key_equal, from the index 0 until the length of key_equal, it's always met at the beginning.
        {
            value_env = ft_substr(envp[i], key_equal_len, ft_strlen(envp[i]));
           if (!value_env)
                malloc_failure(state);
            return (value_env);
        }
        i++;
    }
    return (NULL);
}

void    update_envp_value(char ***envp, char *key_equal, char *value_inp, t_shell_state *state)
{
    int i;
    char *new_str;

    i = 0;
    while((*envp)[i])
    {
        if(ft_strnstr((const char *)(*envp)[i], (const char *)key_equal, ft_strlen(key_equal)) != NULL)// find the envp
        {
            int new_str_len = ft_strlen(key_equal) + ft_strlen(value_inp) + 1;
            new_str = malloc(new_str_len); //create a new empty string        
            if (!new_str)
                malloc_failure(state);
            ft_strlcpy(new_str, key_equal, ft_strlen(key_equal)+1);
            ft_strlcat(new_str, value_inp,new_str_len);

            free((*envp)[i]);
            (*envp)[i] = new_str;
            return;
        }
        i++;
    }    
   
}

int ft_export(char **cmd_argv, char ***envp, t_shell_state *state)
{
    char *input = cmd_argv[1];
    char *key_inp;
    char *key_equal;
    char *value_inp;
    char *value_env;
    int input_len = ft_strlen(input);    
    
    extract_key_and_value(input, input_len, &key_inp, &value_inp, state);
    key_equal = ft_strjoin(key_inp, "=");
    int key_equ_len = ft_strlen(key_equal);
    if (!key_equal)
    {
        free(key_inp);
        free(value_inp);
        g_exit_status = 1;
        return(g_exit_status);
    }        
    if (input)
    {
        if(!contains_equal_sign(input))//if input contains just "key" no '='
        {            
            if(!already_exists(*envp, key_equal, key_equ_len))//if key doesn't exists at all
            {
                add_envp(envp, key_equal, state); //just add "key="
            }
        }
        else // if input has "key=..."
        {
            if(!already_exists(*envp, key_equal, key_equ_len)) //if key doesn't exist in envp
            {
                add_envp(envp, input,state); //just add "key=..." , all the input
            }
            else //if "key=..." exists
            {
                value_env = get_env_value(*envp, key_equal, state);
                if(ft_strcmp(value_env, value_inp) != 0) //if the values are different update the env
                    update_envp_value(envp, key_equal, value_inp, state);
                free(value_env);                
            }
        }
    }
    free(key_inp);   
    free(value_inp);
    free(key_equal);
    g_exit_status = 0;
    return(g_exit_status); 
}

/*
NO need to support:
VAR=value             ❌ (no export)

minishell ONLY needs to handle:
export VAR=value      ✅ store/update VAR
export VAR            ✅ add VAR if it doesn't exist (with empty value):


| Case                        | Why `export MYVAR` matters?                   |
| --------------------------- | --------------------------------------------- |
| Already in `envp`           | No effect, but allowed (harmless)             |
| Not defined at all          | Creates it with empty value                   |
*/