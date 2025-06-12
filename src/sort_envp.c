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
    if(!currentx || !currenty)
        return;    
    update_prev_of_swaped(&currenty, &prevx, head);
    update_prev_of_swaped(&currentx, &prevy, head);
    update_next_of_swaped(&currentx, &currenty);
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
