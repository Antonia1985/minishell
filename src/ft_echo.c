#include "minishell.h"
#include "libft.h"

void remove_char(char *str, char unwanted)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(str[i])
    {
        if(str[i] != unwanted)
        {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
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
            {
                free_array(envp);
                malloc_failure(state);
            }
            return (value_env);
        }
        i++;
    }
    return (NULL);
}

char    *replace_with_value_if_needed(char ** envp, char *final_str, t_shell_state *state)
{
    if (final_str[0] && final_str[0] == '$')
    {
        if(final_str[1] == '?')
        {
            char *value = ft_itoa(g_exit_status);
            if(!value)          
                malloc_failure(state);
            return value;
        }
        else
        {
            const char *key = final_str + 1;
            char *key_equal = ft_strjoin(key, "=");
            if(!key_equal)
            {
                free_array(envp);
                malloc_failure(state);
            }
            if(already_exists(envp, key_equal, ft_strlen(key_equal)))
            {           
                char *value = get_env_value(envp, key_equal, state);
                free(key_equal);
                return value;
            }
            free(key_equal);
            return ft_strdup("");
        }
    }
    return (ft_strdup(final_str));
}

char *final_string(char **cmd_argv, int i, char **envp, t_shell_state *state)
{
    char *tmp;
    char *final_str;
    char *arg;

    // final_str is now the first word (possibly replaced with env value)
    final_str = replace_with_value_if_needed(envp, cmd_argv[i], state);
    if (!final_str)
    {
        free_array(envp);
        malloc_failure(state);
    }
    i++;
    while (cmd_argv[i])
    {
        // Add a space
        tmp = final_str;
        final_str = ft_strjoin(tmp, " ");
        free(tmp);
        if (!final_str)
        {
            free_array(envp);
            malloc_failure(state);
        }
        // Replace with env value if needed
        arg = replace_with_value_if_needed(envp, cmd_argv[i], state);
        if (!arg)
        {
            free_array(envp);
            malloc_failure(state);
        }

        // Append to the final string
        tmp = final_str;
        final_str = ft_strjoin(tmp, arg);
        free(tmp);
        free(arg);
        if (!final_str){
            free_array(envp);
            malloc_failure(state);
        }
        i++;
    }
    remove_char(final_str, '\"');
    return final_str;
}

int    ft_echo(char **cmd_argv, t_env **env_list, t_shell_state *state)
{    
    char **envp;
    int i;

    envp = env_list_to_envp(*env_list, state);
    if(!cmd_argv[1])// NULL argumnet , NOT -n
    {
        printf("\n");
    }
    else if(ft_strcmp(cmd_argv[1], "-n") == 0 && (cmd_argv[2])) // -n + argument
    {
        i = 2;
        while(cmd_argv[i] && ft_strcmp(cmd_argv[i], "-n") == 0)
            i++;
        if (!cmd_argv[i])
        {
            //free_array(envp);
            return(0);
        }            
        char *final_str = final_string(cmd_argv, i, envp, state);
        write(1, final_str, ft_strlen(final_str));
        free(final_str);
    }
    else if(ft_strcmp(cmd_argv[1], "-n") !=0)// argument only
    {
        i = 1;
        char *final_str = final_string(cmd_argv, i, envp, state);
        printf("%s\n",final_str);
        free(final_str);
    }
    free_array(envp);
    return (0);
}