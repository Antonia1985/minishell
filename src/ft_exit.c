#include "minishell.h"
#include "libft.h"

int is_numeric(char *str)
{
    int i;
      
    i = 0;
     if (!str || str[0] == '\0')
        return 0;
    if(str[0] == '+' || str[0] == '-')
        i++;
    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return (1);
}

int	ft_atoi_strict(const char *nptr, long long *num)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	 while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
        i++;
	if ((nptr[i] == '+' || nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			sign = -1;		
		i++;
	}
    if (nptr[i] == '\0')
    {
        return(0);
    }        
	while ((nptr[i] != '\0') && (nptr[i] >= 48) && (nptr[i] <= 57))
    {
        if (*num > (LLONG_MAX - (nptr[i] - '0')) / 10)
            return 0;
        *num = (*num * 10) + (nptr[i++] - '0');
    }		
	*num = *num * sign;	
    return (1);
}

int ft_exit(char **cmd_argv, t_env **env_list, t_shell_state *state)
{    
    (void)env_list;
    long long num = 0;
    int status;

    if (!cmd_argv[1])
    {
        exit_with_status(g_exit_status, state); 
    }
    if (!is_numeric(cmd_argv[1]) || ft_atoi_strict(cmd_argv[1], &num) == 0)
    {
        fprintf(stderr, "exit: %s: numeric argument required\n", cmd_argv[1]);
        exit_with_status(255, state);
    }
    if (cmd_argv[2])
    {
        fprintf(stderr, "exit: too many arguments\n");
        g_exit_status = 1;
        return(g_exit_status);
    }
    status = ((int)num % 256 + 256) % 256;
    printf("exit\n");
    g_exit_status = status;
	return(g_exit_status);
    //exit_with_status(status, state);
}
//exit stauts accepts: 0 - 255, in any case is safer to calculate: status = status % 256;
