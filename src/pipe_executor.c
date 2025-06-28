#include "minishell.h"
#include "libft.h"

//cat file.txt | grep word | wc -l

void    on_execve_failure(char **envp, char *path, t_shell_state *state)
{
    free(path); // only runs if execve fails
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

void    pipe_fail()
{
    perror("pipe");
    exit(1);
}

void    pipe_executor(t_command *cmd, t_shell_state *state, pid_t *pids, int *pid_count)
{
    char **envp;
    int prev_pipe[2];
    int current_pipe[2];

    prev_pipe[0]= STDIN_FILENO;
    prev_pipe[1]=-1;
      
    while(cmd)
    {
        if(cmd->has_pipe && cmd->next)// if pipe follows create a pipe
        {
            if(pipe(current_pipe) == -1)
                pipe_fail();
        }
        else // if it's the last 
        {
            current_pipe[0] = -1;
            current_pipe[1] = STDOUT_FILENO;
        }

        pids[*pid_count] = fork();
        fork_fail(pids[*pid_count]);
        if(pids[*pid_count] == 0)
        {
            envp = env_list_to_envp(state->env_list, state);
            if(prev_pipe[1] != -1) //if this is not the 1st cmd1 |
            {
                close(prev_pipe[1]);                
            }
            if(prev_pipe[0] != STDIN_FILENO)//if this is not the 1st cmd1 |
            {
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
            }

            if(current_pipe[0] != -1) //if this is not the last | cmd. The last won't have a real current pipe
            {
                close(current_pipe[0]);
            }           
            if(current_pipe[1] != STDOUT_FILENO)  //if this is not the last | cmd
            {
                dup2(current_pipe[1], STDOUT_FILENO);
                close(current_pipe[1]);
            }

            if(is_builtin(cmd->argv[0]))
            {
                int status = execute_builtin(cmd, state);
                clean_up_all(state, 0);
                free_array(envp);
                exit(status);
            }	
            else 
            {
                if (!cmd->argv || !cmd->argv[0])
                {
                    fprintf(stderr, "minishell: empty command\n");
                    free_array(envp);
                    clean_up_all(state, 0);
                    exit(127);
                }
                if (cmd->has_redirection && !apply_redirections(cmd, state))  //debug << : dup2(current_pipe[1], STDOUT_FILENO); STDOUT_FILENO : 1  and pipefd[0](pipefd[1] had the heredoc lines and it's closed)
                    exit_with_status(g_exit_status, state);
                //new add
                if (cmd->heredoc && prev_pipe[0] != STDIN_FILENO && prev_pipe[0] != -1)
                    close(prev_pipe[0]);
                //
                char *path = get_full_path(cmd->argv[0], state->path_list, state);
                if (!path)
                {
                    fprintf(stderr, "minishell: %s: command not found\n", cmd->argv[0]);
                    free_array(envp);
                    clean_up_all(state, 0);
                    exit(127);
                }
                //fprintf(stderr, "EXECUTING: %s\n", cmd->argv[0]); ///delete it
                execve(path, cmd->argv, envp);               
                on_execve_failure(envp, path, state);
            }
        }
        //parent 
        (*pid_count)++;      
        //close what you have to close
        if(prev_pipe[0] != STDIN_FILENO) // if it's not the 1st
            close(prev_pipe[0]);
        if(current_pipe[1] != STDOUT_FILENO) //if it'not the last cmd
            close(current_pipe[1]);
        if (!cmd->next && current_pipe[0] != -1) // Check if it's the last command and current_pipe[0] is a real FD
            close(current_pipe[0]);
        // current becomes previous ()
        prev_pipe[0] = current_pipe[0];
        prev_pipe[1] = current_pipe[1];

        //next command
        if(cmd->next)
            cmd = cmd->next;
        else
            break;
    }
    if (prev_pipe[0] != STDIN_FILENO && prev_pipe[0] != -1)
        close(prev_pipe[0]);

}

