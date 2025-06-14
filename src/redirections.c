#include "minishell.h"
#include "libft.h"

int redirection_type(t_command *cmd)
{
	if (cmd->infile) // <
		return(1);
	if (cmd->outfile && !cmd->append) // >
		return (2);
	if(cmd->outfile && cmd->append) // >>
		return (3);
	//if(cmd->heredoc)
		//return (4);
	return (0);
}

void    redirect_fd(char *file, int redirection_type)
{
    int fd;

    if(redirection_type == 1)   // < 
        fd = open(file, O_RDONLY);
    if(redirection_type == 2)
        fd = open(file, O_CREAT | O_WRONLY |O_TRUNC, 0644);    // >
    if(redirection_type == 3)
        fd = open(file, O_CREAT | O_WRONLY |O_APPEND, 0644);   // >>
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    if(redirection_type == 1)   // < 
    {
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
    }
    else if(redirection_type == 2 || redirection_type == 3)
    {
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
    }    
    close (fd);
}

void    here_doc(char *delimeter, t_env *env_list, t_shell_state *state)
{
    char   *line;
    char   *expanded_line;
    char    **input;    
    int     i;
    int     capacity;
    int     expansions; /* must be set from parser */;

    i = 0;
    
    capacity = 20;
    expanded_line = NULL;
    input = malloc(capacity * sizeof(*input));
    if (!input)
        malloc_failure(state);
    input[i] = NULL;
    ft_bzero(input, capacity * sizeof *input);
    expansions = 1;
    if (ft_strchr(delimeter, '\'') || ft_strchr(delimeter, '\"'))
        expansions = 0;

    while(1)
    {        
        line = readline("");
        input[i+1] = NULL;         
        if(!line || ft_strcmp(line, delimeter) == 0)
        {
            //Stop collecting input
            printf("warning: here-document at line 1 delimited by end-of-file (wanted `%s')", delimeter);
            while(input[i])
                printf("%s", input[i]);
            //return all the read lines
             free(line);          // ✓ this is correct
            input[i] = NULL;
            break;
        }
        if( i >= capacity -1)
        {
            input= ft_realloc(input, capacity, capacity*2);
            capacity *= 2;
        }       
        if(expansions)
        {            
            expanded_line = expand_line(line, env_list, state);    
            input[i] = ft_strdup(expanded_line);
        }
        else
        {
            input[i] = ft_strdup(line);
            free(line);
        }
        i++;
        
    }
    i = 0;
    while(input[i])
        printf("%s", input[i]);

}

void    apply_redirections(t_command *cmd)
{
    int redir_type;

    redir_type = redirection_type(cmd);
    if(redir_type == 1)
        redirect_fd(cmd->infile, 1);
    if(redir_type == 2)
        redirect_fd(cmd->outfile, 2);
    if(redir_type == 3)
        redirect_fd(cmd->outfile, 3);
}

/*
Next Steps
< (input redirection): use open(..., O_RDONLY) then dup2(fd, STDIN_FILENO).

> (output truncate): use open(..., O_CREAT|O_WRONLY|O_TRUNC, mode) then dup2.

>> (output append): use open(..., O_CREAT|O_WRONLY|O_APPEND, mode) then dup2.

<< delim (here-doc): you can read lines in a loop from STDIN_FILENO 
    until you see your delimiter.
    
_______________________________________________________________________________________


1)  open() gives you a new FD (say, 3).

2)  dup2(fd, STDIN_FILENO) (i.e. dup2(3, 0)) 
    makes FD 0 point at the same file.

3)  Close the old fd (3) if you don’t need it.
    execve() now sees its standard input coming from your file, not the keyboard.

int fd = open("in.txt", O_RDONLY);
dup2(fd, STDIN_FILENO);   // now reads from in.txt instead of the keyboard
close(fd);
execve(...);

int fd = open("out.txt", O_CREAT|O_WRONLY, 0644);
int copy = dup(fd);
// now both `fd` and `copy` write into out.txt
______________________________________________________________________________________

Flags Quick Reference
------------------------------------------------------------
Flag	    Meaning
O_RDONLY	Read-only open
O_WRONLY	Write-only open
O_RDWR	    Read/write open
O_CREAT	    Create file if it doesn’t exist
O_TRUNC	    Truncate file to zero length if it exists
O_APPEND	All writes go to the end of the file (append)
______________________________________________________________________________________

0644 corresponds to rw-r--r--:
------------------------------------------------------------
Owner can read and write
Group can read only
Others can read only
______________________________________________________________________________________

STDIN_FILENO is 0,
STDOUT_FILENO is 1,
STDERR_FILENO is 2,
______________________________________________________________________________________

< (Input Redirection)   
            By default, most programs read from your keyboard (stdin). 
            < tells the shell to take input from a file instead.
            How it works:
            Shell opens file.txt and connects it to the command’s standard input.
            Use case:
            Any program that reads from stdin (e.g. cat, sort, grep, wc)can instead read from a file.

> (Output Redirection, Truncate)
            By default, most programs print to your screen (stdout). 
            > tells the shell to write that output to a file, overwriting any existing content.
            How it works:
            Shell opens (or creates) list.txt, truncates it to zero length, 
            and connects it to the command’s standard output.
            Use case:
            Capturing program results into a fresh file for later review, logs, etc.

3. >> (Output Redirection, Append)
            Like >, but adds the new output to the end of the file instead of erasing it.
            How it works:
            Shell opens (or creates) errors.log in “append” mode, 
            so each new write is tacked on after existing text.
            Use case:
            Keeping a running log across multiple runs of a program.

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