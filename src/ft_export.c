#include "minishell.h"
#include "libft.h"

void    print_exported_list(t_env *head)
{
    t_env *current = head;

    while(current != NULL)
    {
        printf("declare -x %s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void    print_list(t_env *head)//for debugging
{
    t_env *current = head;

    while(current != NULL)
    {
        printf("key:%s   value:%s\n", current->key, current->value);
        current = current->next;
    }
}

t_env   *copy_env_list(t_env *original, t_shell_state *state)
{
    t_env *copy = NULL;
    t_env *prev = NULL; 
    t_env *copy_head = NULL;
    while(original)
    {
        copy = malloc(sizeof(t_env));
        if(!copy)
            malloc_failure(state);

        copy->key = ft_strdup(original->key);
        if(!copy->key)
            malloc_failure(state);

        copy->value= ft_strdup(original->value);
        if(!copy->value)
            malloc_failure(state);

        copy->next= NULL;

        if(!copy_head)
            copy_head = copy;
        else 
            prev->next = copy;

        prev = copy;
        original = original->next;
    }
    return (copy_head);
}

int     already_exists_in_list(t_env *env_list, char *key, int keylen)
{    
    while(env_list)
    {
        if(ft_strnstr((const char *)env_list->key, (const char *)key, keylen) != NULL)
            return(1);
        env_list = env_list->next;
    }
    return(0);
}

void    add_envp_in_list(t_env **env_list, char *key, char *value,  t_shell_state *state, t_env *variables)
{
    t_env *current = *env_list;
    t_env *prev = NULL;
    t_env *new_node = NULL;

    new_node = malloc(sizeof(t_env));
    if(!new_node)
    {
        free_list(variables);
        malloc_failure(state);
    }
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    if(*env_list == NULL)
    {
        *env_list = new_node;
        return;
    }
    while(current)
    {
        prev = current;
        current = current->next;
    }  
    prev->next = new_node;
}

void    update_envp_value(t_env **env_list, char *key, char *value, t_shell_state *state, t_env *variables)
{
    t_env   *current = *env_list;
    while(current)
    {
        printf("current->key = %s, key = %s\n",current->key, key);
        if(ft_strcmp(current->key, key)== 0)
        {
            
            printf("current->value = %s, value = %s\n",current->value, value);
            free(current->value);
            current->value = value;         
            printf("after change: current->value = %s, value = %s\n",current->value, value);   
            if(!current)
            {
                free_list(variables);
                malloc_failure(state);
            }                
        }
        current = current->next;
    }
}

int     contains_invalid_char(t_env *variables)
{   
    int i;

    i = 0;    
    if(variables->key[0] != '_' && !ft_isalpha(variables->key[0]))
        return(1);
    while (variables->key[i])
    {
        if(!ft_isalnum(variables->key[i]) && variables->key[i] != '_' && variables->key[i] != '=')       
            return(1);
        i++;
    }
   return (0);
   
}

int    ft_export(char **cmd_argv, t_env **env_list, t_shell_state *state)
{
    t_env   *copy;
    t_env   *variables;
    int     i;
    //char    *key_equal;
    //int     key_equ_len;
    char    *value_env;
    char    *key_net;//add it only inside the if() that you need it
        
    g_exit_status = 0;
    i = 0;
    while (cmd_argv[i])
        i++;
   
    if (i == 1) //only export, no variables
    {
        copy = copy_env_list(*env_list, state);
        sort_list(&copy);
        print_exported_list(copy);
        free_list(copy);
    }
    else
    {
        variables = env_list_from_envp(cmd_argv+1, state, 0);
        //key_equal = ft_strjoin(variables->key, "=");
        
        //key_equ_len = ft_strlen(key_equal);       
        //print_list(variables);
        //free_list(variables);
        while (variables)
        {
            if (!contains_invalid_char(variables))
            {
                
                if(!contains_equal_sign(variables->key))//if input contains just "key" no '='
                {
                    key_net = ft_strtrim(variables->key, "=");
                    printf("inside if(!contains_equal_sign(key_net)//if input contains just key no '='\n");
                    printf("variables->key:%s --- key_net:%s --- key_equal:\n",variables->key, key_net);                     
                    if(!already_exists_in_list(*env_list, key_net, ft_strlen(key_net)))//if key doesn't exists at all
                    {
                        printf("inside if(!already_exists_in_list(*env_list, key_net, ft_strlen(key_net)))//if key doesn't exists at all\n");
                        printf("variables->key:%s --- key_net:%s --- key_equal:\n",variables->key, key_net );
                        free(key_net);
                        variables->value = ft_strdup("");
                        if (!variables->value )
                            malloc_failure(state);
                        add_envp_in_list(env_list, variables->key,  variables->value, state, variables); //just add "key="
                    }
                    else//if "key" doesn't exist and dosen't have an '=' sign attached, nothing happens, no new input!
                    {
                        free(key_net);
                        variables = variables->next;
                        continue;
                    } 
                }
                else // if input has '='  ie: "key=..."
                {
                    key_net = ft_strtrim(variables->key, "=");
                    printf("else // if input has '='  ie: key=...\n");
                    printf("variables->key:%s --- key_net:%s --- key_equal:\n",variables->key, key_net);
                    //key_net = ft_strtrim(variables->key, "=");
                    if(!already_exists_in_list(*env_list, key_net, ft_strlen(key_net))) //if key doesn't exist in envp
                    {     
                        printf("inside if(!already_exists_in_list(*env_list, key_net, ft_strlen(key_net))) //if key doesn't exist in envp)\n");
                        printf("variables->key:%s --- key_net:%s --- key_equal:\n",variables->key, key_net);                   
                        add_envp_in_list(env_list, key_net, variables->value, state, variables); //just add "key=..." , all the input
                    }
                    else //if "key=..." exists
                    {
                        printf("else //if key=... exists\n");
                        printf("variables->key:%s --- key_net:%s --- key_equal:\n",variables->key, key_net);                   
                        value_env = get_env_list_value(*env_list, key_net);
                        if(ft_strcmp(value_env, variables->value) != 0) //if the values are different update the env
                        {
                            printf("if(ft_strcmp(value_env, variables->value) != 0) //if the values are different update the env\n");
                            printf("variables->key:%s --- key_net:%s --- key_equal:\n",variables->key, key_net);
                            update_envp_value(env_list, key_net, variables->value, state, variables);
                        }
                        else  //if "key=..." exists and variables are the same, nothing happens, continue;
                        {
                            free(key_net);
                            variables = variables->next;
                            continue;
                        }
                                                
                    }
                }
            }
            else
            {
                if (variables->value)
                    printf("bash: export: `%s%s': not a valid identifier\n", variables->key,variables->value);
                else
                    printf("bash: export: `%s': not a valid identifier\n", variables->key);            
                g_exit_status = 1;                
            }                  
            variables = variables->next;
        }
        
       
        free_list(variables);        
    }

    return(g_exit_status); 
}

/*
about variables, the keys of export:
First character:
Must be a letter (A–Z or a–z) or underscore (_).
Cannot be a digit.

Subsequent characters:
May be letters (A–Z, a–z), digits (0–9), or underscore (_).



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
