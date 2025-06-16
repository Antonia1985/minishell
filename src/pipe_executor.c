#include "minishell.h"
#include "libft.h"
void    on_execve_failure(char **envp, t_shell_state *state)
{
    free_array(envp);
    perror("minishell: execve ");
    clean_up_all(state, 1);
    printf("exit\n");
    g_exit_status = 126;
    exit(126);
}

int    pipe_executor(t_command *cmd, t_shell_state *state, pid_t *pids, int *pid_count)
{
    //cmd = "cat file.txt | "
    int i = 0;
    char **envp;
    int fd[2];
    //make a pipe
    if(pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    //first fork
    pid_t pid1 = fork();
    if(pid1 == -1)
    {
        perror("fork");
        exit(1);
    }
    //child writer   
    if(pid1 == 0) 
    {
        envp = env_list_to_envp(state->env_list, state);
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);       
        execve(state->full_path, cmd->argv, envp); //or execute_builtin
        on_execve_failure(envp, state);
    }
    //parent
    //gather pid
    pids[*pid_count] = pid1;
    (*pid_count)++;
    //find next cmd
    if(cmd->next)//cmds = "grep word | "
    {
        cmd = cmd->next; 
        free(state->full_path);
        state->full_path = get_full_path(cmd->argv[0], state->path_list, state);
        //write(1, cmd->argv[0], strlen(cmd->argv[0]));
        //write(1, "\n",1);
       // write(1, state->full_path, strlen(state->full_path));
        //write(1, "\n",1);
    }
    //second fork
    pid_t pid2 = fork();
    if(pid2 == -1)
    {
        perror("fork");
        exit(1);
    }
    //child reader
    if(pid2 == 0) 
    {
        envp = env_list_to_envp(state->env_list, state);
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);            
        execve(state->full_path, cmd->argv, envp); //or execute_builtin
        on_execve_failure(envp, state);
    }
    //parent
    //gather pid
    pids[*pid_count] = pid2;
    (*pid_count)++;
    //close the pipe
    close(fd[0]);
    close(fd[1]);
    //if more pipe cmds - find next cmd
    if (cmd->has_pipe && cmd->next) //cmds = "wc -l"
    {
        cmd = cmd->next;
        free(state->full_path);
        state->full_path = get_full_path(cmd->argv[0], state->path_list, state);
        //write(1, cmd->argv[0], strlen(cmd->argv[0]));
        //write(1, "\n",1);
        //write(1, state->full_path, strlen(state->full_path));
        //write(1, "\n",1);
        //start from the beginning
        pipe_executor(cmd, state, pids, pid_count);
    }
    if (cmd->next == NULL) // only the last parent will call waitpid() for all child PIDs.
    {
        int status;
        while(i < *pid_count) 
        {
            waitpid(pids[i], &status, 0);
            i++;
        }
        if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status)); // Bash does this!
		else
			return (1);
    }
    return(1);
}