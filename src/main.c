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

int	get_input(char **input, t_env *env_list, t_shell_state *state)
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
	if ((*input)[0] == '\0')
	{
		free(*input);
		return(1);
	}

	*input = expand_line(*input, env_list, state);
	if(!*input)
		malloc_failure(state);

	state->input = *input;
	return(2);
}

int needs_fork(t_command *cmd) 
{
   return (cmd->has_pipe || cmd->heredoc);
}

int dispatcher(t_command *cmd, t_shell_state *state, pid_t *pids, int *pid_count)
{
	if (!cmd->has_pipe)
	{
		if (is_builtin(cmd->argv[0]))// if it's builtin, with or without redirs
		{
			//printf("entered in: !cmd->has_pipe + is_builtin(cmd->argv[0]) \n"); //delete it			
			g_exit_status = execute_builtin(cmd, state);
		}
		else if (state->full_path)// if it's exter, with or without redirs
		{
			//printf("entered in: !cmd->has_pipe + state->full_path \n"); //delete it
			g_exit_status = execute_external(cmd, state->full_path, state); //for here			
		}
		else
		{
			//fprintf(stderr, "%s: command not found\n", cmd->argv[0]); //"minishell: %s: command not found\n"
			g_exit_status = 127;
		}
	}
	else
	{
		int i = 0;
		//printf("entered in: else cmd->has_pipe \n"); //delete it
		pipe_executor(cmd, state, pids, pid_count);
			if (cmd->next == NULL) // only the last parent will call waitpid() for all child PIDs.
		{
			int status;
			while(i < *pid_count) 
			{
				waitpid(pids[i], &status, 0);
				i++;
			}
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = (128 + WTERMSIG(status)); // Bash does this!
			else
				g_exit_status = 1;
		}
    	
	}	
	return(g_exit_status);
}

int main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;

	signals_handler();
	t_env *env_list = env_list_from_envp(envp, NULL, 1);
	while (1)
	{
		pid_t pids[256];
    	int pid_count = 0;
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
						
		int input_res = get_input(&input, env_list, state);
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
		t_command *cmd = parse_input(input);
		state->cmd = cmd;		
		state->path_list = get_path_list(state);
		state->full_path = get_full_path(cmd->argv[0], state->path_list, state);
		
		g_exit_status = dispatcher(cmd, state, pids, &pid_count);		
		clean_up_all(state, 0);

	}
	free_list(env_list);
	rl_clear_history();
	return(g_exit_status);
}

/*
info to understant dispatcher:
| Builtin | Stand-alone  		| With redirections only (e.g. >, <, >>, <<)| In a pipeline (|) 			 | only_in_parent (<-useless feature) |
|:--------|:----------------	|:------------------------------------------|:-------------------------------|:---------------|
| echo 	  | Parent (no fork)	| Parent (apply redirs → echo) 		        | Child (fork → redirs → echo) 	 |    	0		  |
| pwd 	  | Parent (no fork)	| Parent (apply redirs → pwd) 		        | Child (fork → redirs → pwd) 	 |    	0		  |
| env 	  | Parent (no fork)	| Parent (apply redirs → env) 		        | Child (fork → redirs → env) 	 |    	0		  |
| cd 	  | Parent (no fork)	| Parent (apply redirs → cd) 		        | Child (fork → redirs → cd)⁺ 	 | 		1 		  |
| export  | Parent (no fork)	| Parent (apply redirs → export) 	        | Child (fork → redirs → export)⁺| 		1 		  |
| unset	  | Parent (no fork)	| Parent (apply redirs → unset) 	        | Child (fork → redirs → unset)⁺ | 		1 		  |
| exit 	  | Parent (no fork)	| Parent (apply redirs → exit) 		        | Child (fork → redirs → exit)⁺  | 		1 		  |
| execve  | fork_exectr -> fork	| fork_executor -> redirts -> fork			| pipe_exectr → redirs → execve	 |		0		  |

⁺ Stateful built-ins in a pipeline run in a child, but their effects (CWD, env, or shell exit) do not propagate back to the parent shell.

Parent (no fork) = apply any redirections in the shell process, then call the builtin function so it really changes your shell’s state.

Child (fork) = fork first, set up redirections in the child, then call the builtin (or execve for externals); the parent waits on it.

only_in_parent = 1 flags the four builtins whose state changes (cd/export/unset/exit) must run in the parent when not in a pipeline.
*/