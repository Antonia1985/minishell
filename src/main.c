#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"

int g_exit_status = 0;

void get_current_directory(void)
{
	char *cwd = getcwd(NULL, 0);     // dynamically allocates current directory
	char *home = getenv("HOME");
	int cwd_is_in_home = ft_strncmp(cwd, home, ft_strlen(home));
	int home_len = ft_strlen(home);
	int cwd_len = ft_strlen(cwd);

	if (!cwd)
	{
		write(1, "minishell$ ", 11);
		return;
	}

	if (home && cwd_is_in_home == 0)
	{
		write(1, "minishell:~", 11);
		write(1, cwd + home_len, cwd_len - home_len);
	}
	else
	{
		write(1, "minishell:", 10);
		write(1, cwd, cwd_len);
	}
	write(1, "$ ", 2);
	free(cwd);
}

int	get_input(char ***cmd_argv, char **input, t_shell_state *state)
{
	*input = get_next_line(0);
	if (!*input)
	{
		printf("exit\n");		
		return(0);
	}            
	size_t len = ft_strlen(*input);
	if (len > 0 && (*input)[len - 1] == '\n')
		(*input)[len - 1] = '\0';
	if ((*input)[0] == '\0')
	{
		free(*input);
		return(1);
	}
	*cmd_argv = ft_split(*input, ' ');
	if(!*cmd_argv || !(*cmd_argv)[0])
	{
		free(*input);
		return(1);
	}
	state->input = *input;
	state->cmd_argv = *cmd_argv;
	return(2);
}

char **create_minishel_envp(char **envp)
{
	char ** mini_envp;
	int count = 0;
	int i = 0;
	while(envp[count])
		count++;
	mini_envp = malloc(sizeof(char*) * (count + 1));
	if(!mini_envp)
	{
		g_exit_status = 1;
		exit(g_exit_status);
	}
	while(i < count)		
	{
		mini_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	mini_envp[count] = NULL;
	return (mini_envp);
}

int main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;		
    char **mini_envp = create_minishel_envp(envp);
	while (1)
	{			
		char	*command;
		char	**cmd_argv;	
		char	*input; 
		char	*full_path;
		char	**path_list;
		t_shell_state *state;

		get_current_directory();
		state = malloc(sizeof(t_shell_state));
		if(!state)
		{
			g_exit_status = 1;
			free_array(mini_envp);
			exit(g_exit_status);
		}
		state->mini_envp = mini_envp;

		int input_res = get_input(&cmd_argv, &input, state);
		if(input_res == 0)			
		{
			clean_up_all(state, 1);
			exit(0);
		}
		if(input_res == 1)
			continue;
		
		command = cmd_argv[0];
		path_list = get_path_list(state);		
		full_path = get_full_path(cmd_argv[0], path_list, state);

		if (ft_strcmp(command, "$?") == 0)
			command  = ft_itoa(g_exit_status);
		if (is_builtin(command))
		{
			g_exit_status = execute_builtin(cmd_argv, state);
			mini_envp = state->mini_envp;
		}			
		else if (exists_in_path(command, state))
		{
			g_exit_status = execute(cmd_argv, mini_envp, full_path, path_list, state);			
		}
		else
		{
			fprintf(stderr, "minishell: %s: command not found\n", command);
    		g_exit_status = 127;
		}
		clean_up_all(state, 0);
	}
	if (mini_envp)
    	free_array(mini_envp);
	return(g_exit_status);
}
/*
Macro				Description

WIFEXITED(status)	Child exited normally with exit()
WEXITSTATUS(status)	Exit code (e.g. exit(0) → 0)
WIFSIGNALED(status)	Child was killed by a signal
WTERMSIG(status)	Signal that killed the child
*/