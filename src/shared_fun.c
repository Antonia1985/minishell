#include "minishell.h"
#include "libft.h"

void	clean_up_all(t_shell_state *state, int free_env)
{
	if(state->input)
		free(state->input);
	if (state->cmd)
		free_command_list(state->cmd);
	if (state->full_path)
		free(state->full_path);
	if (state->path_list)
		free_array(state->path_list);
	if (free_env && state->mini_envp)
		free_array(state->mini_envp);
	if (free_env && state->env_list)
		free_list(state->env_list);
	if(free_env && state->original_stdin_fd != -1)
	{
        close(state->original_stdin_fd);
        state->original_stdin_fd = -1; // Important: Mark as closed
    }
	free(state);
}

void    malloc_failure(t_shell_state *state)
{
    perror("minishell: malloc");
    clean_up_all(state, 1);
    g_exit_status = 1;
	rl_clear_history();
	
    exit(g_exit_status);
}

void	exit_with_status(int status, t_shell_state *state)
{
	printf("exit\n");
	clean_up_all(state, 1);
	g_exit_status = status;
	exit(g_exit_status);
}

int already_exists(char **envp, char *input, int input_len)
{
    int i = 0;
    while(envp[i])
    {
        if(ft_strnstr((const char *)envp[i], (const char *)input, input_len) != NULL)
            return(1);
        i++;
    }
    return(0);
}

int	contains_equal_sign(char *input)
{
    if (ft_strchr((const char*)input, '=') != NULL)
        return (1);
    return (0);
}

void	free_list(t_env *list)
{
	t_env *temp = list;

	while(list)
	{
		temp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = temp;
	}
	free(list);
}

void	free_array(char **array)
{
	int i;

	i = 0;
	if (!array)
        return;
	while(array[i])
	{
		free(array[i]);
		i++;
	}			
	free(array);
}

void	print_warning_set_status(char *msg, char *insert[], int status)
{
	int	i = 0;
	int j = 0;
   
	while(msg[i])
	{		
		if (msg[i] == '%' && msg[i + 1] == 's')
		{
			write(2, insert[j], ft_strlen(insert[j]));
			j++;
			i += 2;
		}
		else
		{
			write(2, &msg[i], 1);
				i++;
		}
	}
	if (status != -1)
		g_exit_status = status;
}
