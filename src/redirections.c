#include "minishell.h"
#include "libft.h"

int    redirect_fd(int *last_input_fd, t_redir *redir, char *file, int redirection_type, t_shell_state *state)
{
    int fd;
    char *exp_file = expand_line(file, state);
    if (!exp_file || exp_file[0] == '\0' || ft_strchr(exp_file, ' ') != NULL)
    {
        print_warning_set_status("minishell: %s: ambiguous redirect\n",
                                (char*[]){exp_file, NULL}, 1);
        return (0);
    }
    redir->target = exp_file;
    
    if(redirection_type == R_INPUT)   // < 
    {
        fd = open(exp_file, O_RDONLY);
        *last_input_fd = fd;
        //last_input_type = 0;
    }
    else if(redirection_type == R_OUTPUT)
    {
        fd = open(exp_file, O_CREAT | O_WRONLY |O_TRUNC, 0644);    // >
        //*last_output_fd = fd;
    }
    else if(redirection_type == R_APPEND)
    {
        fd = open(exp_file, O_CREAT | O_WRONLY |O_APPEND, 0644);   // >>
        //*last_output_fd = fd;
    }
    else 
    {
        print_warning_set_status("minishell: internal error: unknown redirection type\n", NULL, 2); // <-this warning is not necessary, it's for my debugging, I can keep or delete it
        return (0);
    }
    if (fd < 0)
    {
        char *input_msgs[] = {exp_file, strerror(errno), NULL};
        print_warning_set_status("minishell: %s: %s\n", input_msgs, 1);       
        return (0);
    }

    if (redirection_type == R_APPEND || redirection_type == R_OUTPUT)
    {
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("minishell: dup2");
            close(fd);
            return (0);
        }
        close (fd);
    }   
    return (1);// point 6
}

int    apply_redirections(t_command *cmd, t_shell_state *state)
{
    t_redir *redir = cmd->redir_list;
    int last_hd_fd = -1;
    int last_input_fd = -1;
    //int last_output_fd = -1;
    //int last_input_type = -1;

    while(redir)
    {
        if ((redir->type == R_INPUT || redir->type == R_OUTPUT || redir->type == R_APPEND) 
                && !redirect_fd(&last_input_fd, redir, redir->target, redir->type, state))
            return (0);
        else if(redir->type == R_HEREDOC)
        {
            redir->read_fd = collect_and_pipe_hd(redir->target, state);
            if (last_hd_fd != -1) //if it's not the 1st heredod_fd
                close(last_hd_fd); // close previous heredoc pipe
            last_hd_fd = redir->read_fd;
            if (last_hd_fd == 0) //ctr+C 
            {
                g_exit_status = 130; //Ctrl+C interrupted heredoc → skip command execution
                return(0);
            }
            cmd->here_doc_read_fd = last_hd_fd;
            last_input_fd = last_hd_fd;
            //last_input_type = 3;
        }
        redir = redir->next;
    }
    if (last_input_fd != -1)
    {
        if (dup2(last_input_fd, STDIN_FILENO) == -1)
        {
            perror("minishell: dup2");
            return 0;
        }
        close(last_input_fd);
    }
    return(1);
}

// ihave to check and modify what happens in apply_redirections() when it's called and returns 0;

/*
✅ What your Minishell should do:
Print a warning:
"minishell: one two: ambiguous redirect"
Set g_exit_status = 1 (or 2 — Bash uses 1)
Do not fork or run the command
Return cleanly to the prompt

✅ Where to return early from
In:
dispatcher() (for single commands)
Or pipe_executor() (skip the process if redirection failed)
Make sure if redirection fails, you don’t call execve() or builtin, 
and you don’t exit() unless you're in a forked child.
*/

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

STDIN_FILENO is 0, read
STDOUT_FILENO is 1, write
STDERR_FILENO is 2, write
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