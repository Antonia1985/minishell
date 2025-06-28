#include "minishell.h"
#include "libft.h"

char 	**get_path_list(t_shell_state *state)
{
	char *path;
	char **pathlist;

	path = getenv("PATH");
	 if (!path)
        return NULL;

	pathlist = ft_split(path, ':');
	if (!pathlist)
        return(NULL);

	state->path_list = pathlist;
	return(pathlist);
}

char	*get_full_path(char *command, char **path_list, t_shell_state *state)
{
	int i;
	char *command_full_path;
	char *temp;

	i =0;
	while(path_list[i])
	{
		temp = ft_strjoin(path_list[i], "/");
		if (!temp)
            malloc_failure(state);
		command_full_path = ft_strjoin(temp, command);
		free(temp);
		if (!command_full_path)	
			malloc_failure(state);
		if (access(command_full_path, F_OK) == 0)
		{
			if (access(command_full_path, X_OK) == 0)
			{
				state->full_path = command_full_path;
				return (command_full_path);
			}
			else 
			{
				char *input_msgs[] = {command_full_path, NULL};
				print_warning_set_status("minishell: %s: Permission denied\n", input_msgs, 126);
				free(command_full_path);
				state->full_path_error = 126;
				return (NULL);
			}
		}
		free(command_full_path);
		i++;
	}
	state->full_path_error = 127;
	return (NULL);
	
}

int execute_external(t_command *cmd, char *full_path, t_shell_state *state)
{		
	pid_t pid;
	char **envp;

	pid = fork();
	if (pid == 0)// Child process
	{	
		//printf("entered in: execute_fork of fork_executor\n"); //delete it
		envp = env_list_to_envp(state->env_list, state);		
		
		if(cmd->has_redirection && !apply_redirections(cmd, state))
        	exit_with_status(g_exit_status, state);
		
		execve(full_path, cmd->argv, envp);
		free_array(envp);
		perror("minishell: execve");
		clean_up_all(state, 1);
		printf("exit\n");
		g_exit_status = 126;
		exit(126);
		//}
	}
	else if(pid > 0) // Parent process
	{
		int status;
		waitpid(pid, &status, 0);
       	if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status)); // Bash does this!
		else
			return (1);
	}
	else 
	{
		perror("minishell: fork");		
        return (1);
	}
	return(1);
}
/*
Macro				Description

WIFEXITED(status)	Child exited normally with exit()
WEXITSTATUS(status)	Exit code (e.g. exit(0) → 0)
WIFSIGNALED(status)	Child was killed by a signal
WTERMSIG(status)	Signal that killed the child
*/