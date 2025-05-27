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

char    *final_string(char **cmd_argv, int i)
{   
    char *final_str = ft_strdup(cmd_argv[i]);
    i++;
    while (cmd_argv[i])
    {
        char *tmp = final_str;
        final_str = ft_strjoin(tmp, " ");
        free(tmp);

        tmp = final_str;
        final_str = ft_strjoin(tmp, cmd_argv[i]);
        free(tmp);
        i++;
    }        
    remove_char(final_str, '\"');
    return(final_str);
}

int    ft_echo(char **cmd_argv)
{     
    int i;

    if(!cmd_argv[1])// NULL argumnet , NOT -n
    {
        printf("\n");
    }
    else if(ft_strcmp(cmd_argv[1], "-n") == 0 && (cmd_argv[2])) // -n + argument
    {
        printf("%s",cmd_argv[2]);
       
        /*i = 2;
        while(cmd_argv[i] && ft_strcmp(cmd_argv[i], "-n") == 0)
            i++;
        if (!cmd_argv[i])
            return(0);
        char *final_str = final_string(cmd_argv, i);
        printf("%s",final_str);
        free(final_str);*/
    }
    else if(ft_strcmp(cmd_argv[1], "-n") !=0)// argument only
    {
        i = 1;
        char *final_str = final_string(cmd_argv, i);
        printf("%s\n",final_str);
        free(final_str);
    }
    return (0);
}