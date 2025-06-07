#include "minishell.h"
#include "libft.h"

void    find_node_by_value(char *x, t_env **currentx, t_env **prevx, t_env **head)
{
    *currentx = *head;
    *prevx = NULL;
    while(*currentx && (ft_strcmp((*currentx)->key, x) != 0))
    {
        *prevx = *currentx;
        *currentx = (*currentx)->next;
    }
}

void    update_prev_of_swaped(t_env **current, t_env **prev, t_env **head)
{
    if(*prev)
        (*prev)->next = *current;
    else
        *head = *current; 
    
}

void    update_next_of_swaped( t_env **currentx,  t_env **currenty)
{
    t_env *temp = NULL;
    if ((*currentx)->next == (*currenty))
    {
        (*currentx)->next = (*currenty)->next;
        (*currenty)->next = (*currentx);
    }
    else if((*currenty)->next == (*currentx))
    {
        (*currenty)->next = (*currentx)->next;
        (*currentx)->next = (*currenty);
    }
    else
    {
        temp = (*currentx)->next;
        (*currentx)->next = (*currenty)->next;
        (*currenty)->next = temp;
    }
}

void    swap_nodes_strings(t_env **head, char *x, char *y)
{
    if(ft_strcmp(x, y) == 0)
        return;
    t_env *prevx= NULL;
    t_env *prevy= NULL;
    t_env *currentx= NULL;
    t_env *currenty= NULL;   

    find_node_by_value(x, &currentx, &prevx, head);
    find_node_by_value(y, &currenty, &prevy, head);
    /*currentx = *head;
    while(currentx && (ft_strcmp(currentx->key, x) != 0))
    {
        prevx = currentx;
        currentx = currentx->next;
    }
    currenty = *head;
    while(currenty && (ft_strcmp(currenty->key, y) != 0))
    {
        prevy = currenty;
        currenty = currenty->next;
    }*/
    if(!currentx || !currenty)
        return;    
    
    update_prev_of_swaped(&currenty, &prevx, head);
    update_prev_of_swaped(&currentx, &prevy, head);
    /*if(prevx)
        prevx->next = currenty;
    else
        *head = currenty;    
    if(prevy)
        prevy->next = currentx;
    else 
        *head = currentx;
    */
    update_next_of_swaped(&currentx, &currenty);
    /*if (currentx->next == currenty)
    {
        currentx->next = currenty->next;
        currenty->next = currentx;
    }
    else if(currenty->next == currentx)
    {
        currenty->next = currentx->next;
        currentx->next = currenty;
    }
    else
    {
        temp = currentx->next;
        currentx->next = currenty->next;
        currenty->next = temp;
    }*/
}

void    sort_list(t_env **env_head)
{
    t_env *min = *env_head;
    t_env *current = NULL;
    int swapped;

    if (!env_head || !(*env_head))
        return;

    swapped = 1;
    while(swapped)
    {
        swapped = 0;
        min = *env_head;        
        while(min && min->next)
        {
            current = min->next;
            if(ft_strcmp(min->key, current->key) > 0)
            {
                swap_nodes_strings(env_head, min->key, current->key);
                swapped = 1;   
                break;          
            }         
            min = min->next;
        }                     
    }
}

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

int already_exists_in_list(t_env *env_list, char *key, int keylen)
{    
    while(env_list)
    {
        if(ft_strnstr((const char *)env_list->key, (const char *)key, keylen) != NULL)
            return(1);
        env_list = env_list->next;
    }
    return(0);
}

void add_envp_in_list(t_env **env_list, char *key, char *value,  t_shell_state *state, t_env *variables)
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

char    *get_env_list_value(t_env *env_list, char *key)
{
    while(env_list)
    {
        if(ft_strcmp(env_list->key, key)== 0)
        {
            return(env_list->value);
        }
        env_list = env_list->next;
            
    }
    return (NULL);
}

void    update_envp_value(t_env **env_list, char *key, char *value, t_shell_state *state, t_env *variables)
{
    t_env   *current = *env_list;
    while(current)
    {
        if(ft_strcmp(current->key, key)== 0)
        {
            free(current->value);
            current->value = value;
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
    char    *key_equal;
    int     key_equ_len;
    char    *value_env;
    char    *key_net;
        
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
        key_equal = ft_strjoin(variables->key, "=");
        key_equ_len = ft_strlen(key_equal);
       
        //print_list(variables);
        //free_list(variables);
        while (variables)
        {
            if (!contains_invalid_char(variables))
            {
                if(!contains_equal_sign(variables->key))//if input contains just "key" no '='
                {
                    if(!key_equal)
                        malloc_failure(state);  
                    if(!already_exists_in_list(*env_list, key_equal, key_equ_len))//if key doesn't exists at all
                    {
                        variables->value = ft_strdup("");
                        if (!variables->value )
                            malloc_failure(state);
                        add_envp_in_list(env_list, variables->key,  variables->value, state, variables); //just add "key="
                    }//if "key" doesn't exist and dosen't have an '=' sign attached, nothing happens, no new input!
                }
                else // if input has "key=..."
                {
                    key_net = ft_strtrim(variables->key, "=");
                    if(!already_exists_in_list(*env_list, variables->key, ft_strlen(variables->key))) //if key doesn't exist in envp
                    {
                        add_envp_in_list(env_list, key_net, variables->value, state, variables); //just add "key=..." , all the input
                    }
                    else //if "key=..." exists
                    {
                        value_env = get_env_list_value(*env_list, key_net);
                        if(ft_strcmp(value_env, variables->value) != 0) //if the values are different update the env
                            update_envp_value(env_list, variables->key, variables->value, state, variables);
                        
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
*/