#include "minishell.h"
#include "libft.h"

char 	**get_path_list(t_shell_state *state)
{
	char *path = getenv("PATH");
	 if (!path)
        return NULL;

	char **pathlist;
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

	i =0;
	while(path_list[i])
	{
		char *temp = ft_strjoin(path_list[i], "/");
		command_full_path = ft_strjoin(temp, command);
		if (access(command_full_path, X_OK) == 0)
			return (command_full_path);
		free(temp);
		//free(command_full_path);
		i++;		
	}
	state->full_path = command_full_path;
	return (NULL);
}

int	exists_in_path(char *command, t_shell_state *state)
{
	char **path_list;

	path_list = get_path_list(state);
	if (!path_list) {
		perror("get_path_list failed");
		return (1);
	}
	char *full_path = get_full_path(command, path_list, state);
	if(full_path)
		return (1);
	else
	{
		return(0);
	}
	
}

int execute(char **cmd_argv, char *full_path, char **path_list, t_shell_state *state)
{		
	pid_t pid;
	
	pid = fork();
	if (pid == 0)// Child process
	{	
		char **envp = env_list_to_envp(&state->env_list, state);
		execve(full_path, cmd_argv, envp);
		perror("minishell: execve:");
		//free(full_path);
		//free_array(path_list);
		clean_up_all(state, 1);
		printf("exit\n");
		g_exit_status = 126;
		exit(126);
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
		perror("minishell: fork:");
		free(full_path);
		free_array(path_list);
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