#include "minishell.h"
#include "libft.h"

t_env *env_list_from_envp(char **envp, t_shell_state *state, int for_envp)
{
    int     i;
    char    *sep;
    int     key_len;
    char    *key;
    char    *value;
    t_env   *head;
    t_env   *current;

    head = NULL;
    current = NULL;
    i = 0;
    while(envp[i])
    {

        if(for_envp)
        {
            sep = ft_strchr(envp[i], '=');
            if(!sep)
            {
                i++;
                continue;
            }       
            key_len = sep - envp[i];
        }
        else
        {
            sep = ft_strchr(envp[i], '=');
            key_len = sep + 1 - envp[i];
        }
        
        key = ft_substr(envp[i], 0, key_len);
        if(!key)
        {
            if(!state)//nothing to free outside the loop
            {
                perror("minishell: malloc");
                g_exit_status = 1;
                exit(g_exit_status);
            }
            else
                malloc_failure(state);            
        }

        if(sep)
        {
            value = ft_strdup(sep + 1);
            if(!value)
            {
                free(key);
                if(!state)//nothing to free outside the loop
                {
                    perror("minishell: malloc"); 
                    g_exit_status = 1;
                    exit(g_exit_status);
                }
                else
                    malloc_failure(state);            
            }
        }           
        else
            value = NULL;

        t_env *node = malloc(sizeof(t_env));
        if(!node)
        {
            free(key);
            free(value);
            if(!state)//nothing to free outside the loop
            {
                perror("minishell: malloc"); 
                g_exit_status = 1;
                exit(g_exit_status);
            }
            else
                malloc_failure(state);          
        }
        node->key = key;
        node->value = value;
        node->next = NULL;
        if (head == NULL)// first run: make head point to this new node
            head = node;
        else//next runs: make previous_node->next point this new node
            current->next = node;
        current = node; // then the current node points to the new node
        i++;
    }
    return (head);
}

char **env_list_to_envp(t_env *list, t_shell_state *state)
{
    int i;
    int list_len;
    char **envp_array;
    char *key_equal;
    t_env *temp;

    temp = list;
    list_len = 0;
    while(temp)
    {
        list_len++;
        temp = temp->next;
    }
    envp_array = malloc(sizeof(char *) * (list_len+1));
    if(!envp_array)
        malloc_failure(state);
    i = 0;
    while(list)
    {
        key_equal = ft_strjoin(list->key, "=");
        if(!key_equal)
            malloc_failure(state);
        envp_array[i] = ft_strjoin(key_equal, list->value);
        free(key_equal);
        if (!envp_array[i])
            malloc_failure(state);
        list = list->next;
        i++;
    }
    envp_array[i] = NULL;
    return (envp_array);
}


/*
| Use Case                 | Should Use Linked List?  |
| ------------------------ | ------------------------ |
| `env`, `export`, `unset` | ✅ Yes                    |
| Commands in a pipeline   | ✅ Yes (common structure) |
| Redirections             | ✅ Yes                    |
| Heredocs (bonus)         | 🟡 Optional              |
| PATH, builtins, history  | ❌ Not needed             |

*/