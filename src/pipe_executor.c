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

void fork_fail(pid_t pid)
{
    if(pid == -1)
    {
        perror("fork");
        exit(1);
    }
}

void    child(int pipefd[2], int std_fileno, t_command *cmd, t_shell_state *state)
{
    if(std_fileno == 0)
        close(pipefd[1]);
    else       
        close(pipefd[0]);
    dup2(pipefd[std_fileno], std_fileno);
    close(pipefd[std_fileno]);
    if(is_builtin(cmd->argv[0]))
    {
        int status = execute_builtin(cmd, state);
        clean_up_all(state, 0);
        free_array(env_list_to_envp(state->env_list, state));
        exit(status);
    }	
    else 
    {
        if(cmd->has_redirection)
            apply_redirections(cmd);   
        execve(state->full_path, cmd->argv, env_list_to_envp(state->env_list, state));
        on_execve_failure(env_list_to_envp(state->env_list, state), state);
    }
}

void    pipe_executor(t_command *cmd, t_shell_state *state, pid_t *pids, int *pid_count)
{
    int child_reader; 
    int pipefd1[2];
    int pipefd2[2];
    int prev_fd_0;
    pid_t pid;

    child_reader = 0;
    while(cmd)
    {
        if(cmd->next && cmd->has_pipe)
        {
            if(pipe(pipefd1) == -1)
            {
                perror("pipe");
                exit(1);
            }
        }
        
        //it's writer
        if(cmd->has_pipe && !child_reader)
        {
            pid = fork();
            fork_fail(pid);
            if(pid == 0)
            {
                close(pipefd1[0]);
                dup2(pipefd1[1], STDOUT_FILENO);
                close(pipefd1[1]);
                if(is_builtin(cmd->argv[0]))
                {
                    int status = execute_builtin(cmd, state);
                    clean_up_all(state, 0);
                    free_array(env_list_to_envp(state->env_list, state));
                    exit(status);
                }	
                else 
                {
                    if(cmd->has_redirection)
                        apply_redirections(cmd);   
                    execve(state->full_path, cmd->argv, env_list_to_envp(state->env_list, state));
                    on_execve_failure(env_list_to_envp(state->env_list, state), state);
                }
            }
            //parent
            close(pipefd1[1]);
            prev_fd_0 = pipefd1[0];
            pids[*pid_count] = pid;
            (*pid_count)++;
            child_reader = 1;
        }
    
        //it's reader && writer   
        if (child_reader && cmd->has_pipe)
        {
            
            pid = fork();
            fork_fail(pid);
            if(pid == 0)
            {    
                dup2(pipefd1[0], STDIN_FILENO);
                close(pipefd1[0]);

                dup2(pipefd2[1], STDOUT_FILENO);
                close(pipefd2[1]);
                
                if(is_builtin(cmd->argv[0]))
                {
                    int status = execute_builtin(cmd, state);
                    clean_up_all(state, 0);
                    free_array(env_list_to_envp(state->env_list, state));
                    exit(status);
                }	
                else 
                {
                    if(cmd->has_redirection)
                        apply_redirections(cmd);   
                    execve(state->full_path, cmd->argv, env_list_to_envp(state->env_list, state));
                    on_execve_failure(env_list_to_envp(state->env_list, state), state);
                }
            }
            child_reader = 1;
            pids[*pid_count] = pid;
            (*pid_count)++;
            close(pipefd1[0]);
            close(pipefd2[1]);
            prev_fd_0 = pipefd2[0];
        }
        
        //it's reader only
        if (child_reader && !cmd->has_pipe)
        {
            pid = fork();
            fork_fail(pid);
            if(pid == 0)
            {    
                dup2(pipefd2[0], STDIN_FILENO);
                close(pipefd2[0]);
                
                if(is_builtin(cmd->argv[0]))
                {
                    int status = execute_builtin(cmd, state);
                    clean_up_all(state, 0);
                    free_array(env_list_to_envp(state->env_list, state));
                    exit(status);
                }	
                else 
                {
                    if(cmd->has_redirection)
                        apply_redirections(cmd);   
                    execve(state->full_path, cmd->argv, env_list_to_envp(state->env_list, state));
                    on_execve_failure(env_list_to_envp(state->env_list, state), state);
                }
            }
            child_reader = 0;
            pids[*pid_count] = pid;
            (*pid_count)++;        
            close(prev_fd_0);
        }
        
        //next command
        if(cmd->next)
        {
            cmd = cmd->next;
            free(state->full_path);
            state->full_path = get_full_path(cmd->argv[0], state->path_list, state);        
        }
    }
}

/*
✅ Correct Close Behavior (per command)

Command	    Reads_from	    Writes_to	    Close in child
cmd1	    —	            pipe1[1]	    Close pipe1[0], close pipe1[1] after dup2
cmd2	    pipe1[0]	    pipe2[1]    	Close pipe1[0] + pipe2[1] after dup2, but NOT pipe2[0]
cmd3	    pipe2[0]	    —	            Close pipe2[0] after dup2

*/