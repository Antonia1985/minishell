#include "minishell.h"
#include "libft.h"

int g_exit_status = 0;

char *get_current_directory()
{
	char *cwd = getcwd(NULL, 0);     // dynamically allocates current directory
	char *home = getenv("HOME");
	//int cwd_is_in_home;
	//int home_len = ft_strlen(home);	
	char *prompt;
	char *temp;

	if (!cwd)
		temp = ft_strdup("minishell");
	else if (home && (ft_strncmp(cwd, home, ft_strlen(home)) == 0))
		temp = ft_strjoin("minishell:~", cwd + ft_strlen(home));
	else	
		temp = ft_strjoin("minishell:", cwd);
	prompt = ft_strjoin(temp, "$ ");
	if(cwd)
		free(cwd);
	if(temp)
		free(temp);
	return (prompt);
}

int	get_input(char ***cmd_argv, char **input, t_shell_state *state)
{
	char *prompt = get_current_directory();

	*input = readline(prompt);
	free(prompt);
	if (!*input) //readline() returned NULL on EOF (Ctrl+D)
	{
		printf("exit\n");
		return(0);
	}
	if (**input) // Non-empty input
            add_history(*input);
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

int main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;

	signals_handler();
	t_env *env_list = env_list_from_envp(envp, NULL, 1);
	while (1)
	{			
		char	*command;
		char	**cmd_argv;	
		char	*input;
		t_shell_state *state;

		state = malloc(sizeof(t_shell_state));
		if(!state)
		{
			g_exit_status = 1;
			exit(g_exit_status);
		}
		ft_memset(state, 0, sizeof(t_shell_state));
		state->env_list = env_list;

		int input_res = get_input(&cmd_argv, &input, state);
		if(input_res == 0) //readline() returned NULL on EOF (Ctrl+D)
		{
			rl_clear_history();
			clean_up_all(state, 1);// because of this I dont need to free()state->env_list when out of the loop 
			exit(0);
		}
		if(input_res == 1)
		{
			clean_up_all(state, 0);
			continue;
		}	
		
		command = cmd_argv[0];
		state->path_list = get_path_list(state);
		state->full_path = get_full_path(command, state->path_list, state);

		if (ft_strcmp(command, "$?") == 0)
			command  = ft_itoa(g_exit_status);
		if (is_builtin(command))
		{
			g_exit_status = execute_builtin(cmd_argv, state);			
		}			
		else if (exists_in_path(command, state))
		{
			g_exit_status = execute(cmd_argv, state->full_path, state);			
		}
		else
		{
			fprintf(stderr, "minishell: %s: command not found\n", command);
    		g_exit_status = 127;
			// if (full_path)
            //    free(full_path);
		}
		clean_up_all(state, 0);
	}	
	free_list(env_list);
	rl_clear_history();
	return(g_exit_status);
}
