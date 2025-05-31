#include "minishell.h"
#include "libft.h"

int g_exit_status = 0;

char *get_current_directory()
{
	char *cwd = getcwd(NULL, 0);     // dynamically allocates current directory
	char *home = getenv("HOME");
	int cwd_is_in_home = ft_strncmp(cwd, home, ft_strlen(home));
	int home_len = ft_strlen(home);	
	char *prompt;
	char *temp;

	if (!cwd)
		temp = "minishell";
	if (home && cwd_is_in_home == 0)
		temp = ft_strjoin("minishell:~", cwd + home_len);
	else	
		temp = ft_strjoin("minishell:", cwd);
	prompt = ft_strjoin(temp, "$ ");
	free(cwd);
	if(temp)
		free(temp);
	return (prompt);
}

int	get_input(char ***cmd_argv, char **input, t_shell_state *state)
{
	char *prompt = get_current_directory();

	*input = readline(prompt);
	if (!*input)
	{
		printf("exit\n");
		return(0);
	}
	if (*input && **input) // Non-empty input
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

/*char **create_minishel_envp(char **envp)
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
}*/

int main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;  
	t_shell_state *state;  
	state = malloc(sizeof(t_shell_state));
	if(!state)
	{
		g_exit_status = 1;
		exit(g_exit_status);
	}
	ft_memset(state, 0, sizeof(t_shell_state));
	char *env_list = env_list_from_envp(envp, state);
	while (1)
	{			
		char	*command;
		char	**cmd_argv;	
		char	*input; 
		char	*full_path;
		char	**path_list;
		//t_shell_state *state;

		//get_current_directory();
		/*state = malloc(sizeof(t_shell_state));
		if(!state)
		{
			g_exit_status = 1;
			free_list(env_list);
			exit(g_exit_status);
		}*/
		ft_memset(state, 0, sizeof(t_shell_state));
		state->env_list = env_list;

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
		}			
		else if (exists_in_path(command, state))
		{
			g_exit_status = execute(cmd_argv, full_path, path_list, state);			
		}
		else
		{
			fprintf(stderr, "minishell: %s: command not found\n", command);
    		g_exit_status = 127;
		}
		clean_up_all(state, 0);
	}
	if (env_list)
    	free_list(env_list);
	return(g_exit_status);
}
/*
Macro				Description

WIFEXITED(status)	Child exited normally with exit()
WEXITSTATUS(status)	Exit code (e.g. exit(0) → 0)
WIFSIGNALED(status)	Child was killed by a signal
WTERMSIG(status)	Signal that killed the child
*/