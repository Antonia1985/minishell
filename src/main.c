#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"

int g_exit_status = 0;

void	get_current_directory()
{
	char cwd[1024];
	if(getcwd(cwd, sizeof(cwd)) != NULL)		
	{
		write(1, "minishell:", 10);
		write(1, cwd, ft_strlen(cwd));
		write(1, "$ ", 2);
	}
	else
		write(1, "minishell$ ", 11);
}

int main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;		
	while (1)
	{			
		char *command;
		char **cmd_argv;	
		char *input; 
		char *full_path;
		char **path_list;

		get_current_directory();
		//handle input
		input = get_next_line(0);
		if (!input)
		{
			printf("logout\n");
			break; // Handle Ctrl+D (EOF)
		}            
		size_t len = ft_strlen(input);
		if (len > 0 && input[len - 1] == '\n')
    		input[len - 1] = '\0';
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		cmd_argv = ft_split(input, ' ');
		if(!cmd_argv || !cmd_argv[0])
		{
			free(input);
    		continue;
		}
		
		command = cmd_argv[0];
		//handle $?


		path_list = get_path_list();		
		full_path = get_full_path(cmd_argv[0], path_list);
		//implement sth if it has redrections or pipes etc to decide if fork or not 
		//regarding echo, pwd, env
		if (ft_strcmp(command, "$?") == 0)
			command  = ft_itoa(g_exit_status);
		if (is_builtin(command))
		{
			g_exit_status  = execute_builtin(cmd_argv);
			//return (g_exit_status);
		}
		else if(exists_in_path(command))
		{			
			g_exit_status = execute(cmd_argv, envp, full_path, path_list);
			//return (g_exit_status);
		}
		else 
		{
			fprintf(stderr, "minishell: %s: command not found\n", command);
    		g_exit_status = 127;
		}
		free(input);
		free_array(cmd_argv);   // you need to write this to free char**
		free(full_path);
		free_array(path_list); 
		
	}
	return(g_exit_status);
}
/*
Macro				Description

WIFEXITED(status)	Child exited normally with exit()
WEXITSTATUS(status)	Exit code (e.g. exit(0) → 0)
WIFSIGNALED(status)	Child was killed by a signal
WTERMSIG(status)	Signal that killed the child
*/
