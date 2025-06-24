#include "minishell.h"
#include "libft.h"

void heredoc_sigint_handler(int sig)
{
    (void)sig;
    g_exit_status = 130; // use exit code to indicate Ctrl+C
    write(1, "\n", 1);
    //write(1, "in heredoc_sigint_handler", 18);
    close(STDIN_FILENO); // special code for heredoc interrupted
}

int     collect_and_pipe_hd(t_command *cmd, t_shell_state *state)
{
    char   *line;
    char   *expanded_line;
    char    **input;    
    int     i;
    int     capacity;
    int     expansions; // must be set from parser ;
    struct sigaction sa;
    struct sigaction old_sa;

    sigaction(SIGINT, NULL, &old_sa); // Save current handler

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = heredoc_sigint_handler;
    sigaction(SIGINT, &sa, NULL);// Set new handler (heredoc)
    i = 0;
    capacity = 20;
    expanded_line = NULL;
    input = malloc(capacity * sizeof(*input));
    if (!input)
        malloc_failure(state);
    input[i] = NULL;
    ft_bzero(input, capacity * sizeof *input);
    expansions = 1;
    if (ft_strchr(cmd->heredoc_delim, '\'') || ft_strchr(cmd->heredoc_delim, '\"'))
        expansions = 0;

    while(1)
    {
        line = readline("> ");
        if(!line)
        {
            if(g_exit_status != 130)// If g_exit_status is NOT 130, it means it was Ctrl+D (EOF)
            //Ctrl+D (EOF) is a valid, non-fatal case, heredoc input ends early, but you still want to send the collected lines to the command
            {            
                print_warning("warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", 
                        cmd->heredoc_delim, state);                
            }
            break;// Exit loop whether it's Ctrl+D or Ctrl+C
        }//else if there is >some_input in the line,and I ctr+D nothing happens..
        if(ft_strcmp(line, cmd->heredoc_delim) == 0)        
        {
            //Stop collecting input        
            free(line);// Free the delimiter line
            break;
        }
        if( i >= capacity -1)
        {
            input= ft_realloc(input, capacity, capacity*2);
            if (!input)
            {
                free_array(input);
                malloc_failure(state);
            }
            capacity *= 2;
        }       
        if(expansions)
        {            
            expanded_line = expand_line(line, state->env_list, state);
            input[i] = ft_strdup(expanded_line);
            //free(expanded_line);
            line = expanded_line;
            if(!input[i])
                malloc_failure(state);
        }
        else
        {
            input[i] = ft_strdup(line);
            if(!input[i])
                malloc_failure(state);
        }
        free(line);
        i++;
    }
    //free(line);
    if(input)
        input[i] = NULL;

    int pipefd[2];
    if(pipe(pipefd) == -1)
        pipe_fail();

    i = 0;
    while(input[i])
    {
        write(pipefd[1], input[i], ft_strlen(input[i]));
        write(pipefd[1], "\n", 1);
        i++;
    }
    free_array(input);
    close(pipefd[1]);
    sigaction(SIGINT, &old_sa, NULL);
    cmd->here_doc_read_fd = pipefd[0];
    if (g_exit_status == 130)// ctr+C :  when Ctrl+C is pressed at any point during a line input:
                                    //readline() will: Cancel the current input & Return NULL, that's why: if(!line)
    {
        close(pipefd[0]); // Close the read end too, as the command won't read from it now
        return (0); // Indicate that the heredoc collection was cancelled
    }
    return(1);
}

/*
4. << DELIM (Here-Document)
    A “here-document” feeds inline text into a command until you type a special delimiter word. 
    Useful for providing multi-line input without creating a temporary file.
    How it works:
    Shell sees << EOF and starts reading lines you type.
    Everything up to a line that exactly matches EOF is sent to the command’s stdin.
    The EOF line itself is not included.
    Use case:
    Writing multi-line configurations or emails in a script.
    Embedding input to an interactive program that expects typed lines.
    
    -Unquoted delimiter      → EOF   → do expansions.
    -Single-quoted delimiter → 'EOF' → literal, no expansions.

*/