#define _POSIX_C_SOURCE 200112L
#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>// for LLONG_MAX
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <asm-generic/signal-defs.h>
#include <fcntl.h>

typedef enum e_redir_type {
    R_INPUT,
    R_OUTPUT,
    R_APPEND,
    R_HEREDOC
}   t_redir_type;

typedef struct s_redir {
    t_redir_type type;
    char *target;     // filename or heredoc limiter
    int read_fd;      // only used for heredocs
    struct s_redir *next;
}   t_redir;

typedef struct s_command {
    char **argv;             // Arguments array (execve-compatible)
    //char *infile;          // File name for input redirection ('<')
    //char *outfile;         // File name for output redirection ('>' or '>>')
    //int append;            // 0 = >, 1 = >>
    int heredoc;             // 1 = heredoc used (<<)
    //char *heredoc_delim;   // Delimiter string for heredoc
    int here_doc_read_fd;    // default -1
    int has_redirection;     // 1 = true, 0 = false
    t_redir *redir_list;
    int has_pipe;             // 1 if there's a pipe after this command
    struct s_command *next;   // Next command in pipeline
} t_command;


typedef struct s_env{
    char *key;
    char *value;
    struct s_env *next;
}t_env;

typedef struct s_shell_state{
    char *input;
    t_command *cmd;
    char *full_path;
    char **path_list;
    char **mini_envp;
    t_env   *env_list;
    int original_stdin_fd;
    int full_path_error;
} t_shell_state;

typedef int(*buildin_func)(char **, t_env **, t_shell_state *);

typedef struct s_builtin{
    char    *name;
    buildin_func func;
    int     only_in_parent;
}t_builtin;

extern int  g_exit_status; //check if better: volatile sig_atomic_t g_exit_status;


int		main(int argc, char **argv, char **envp);
int		execute_external(t_command *cmd, char *full_path, t_shell_state *state);
int		execute_builtin(t_command *cmd, t_shell_state *state);
void    pipe_executor(t_command *cmd, t_shell_state *state, pid_t *pids, int *pid_count);
void    pipe_fail();
int		is_builtin(char *command);
int     should_run_in_parent(char *command);
//int		exists_in_path(char *command, t_shell_state *state);
char	**get_path_list(t_shell_state *state);
char	*get_full_path(char *command, char **path_list, t_shell_state *state);

//builtins
int		ft_cd(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_exit(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_echo(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_pwd(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_env(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_export(char **cmd_argv, t_env **env_list, t_shell_state *state);
int		ft_unset(char **cmd_argv, t_env **env_list, t_shell_state *state);


// shared_fun
void	clean_up_all(t_shell_state *state, int free_env);
void	malloc_failure(t_shell_state *state);
void	exit_with_status(int status, t_shell_state *state);
int		already_exists(char **envp, char *input, int input_len);
int		contains_equal_sign(char *input);
void	free_list(t_env *list);
void	free_array(char **path_list);
void	print_warning_set_status(char *msg, char *insert[], int status);

//converter
t_env   *env_list_from_envp(char **envp, t_shell_state *state, int for_envp);
char    **env_list_to_envp(t_env *list, t_shell_state *state);

//signals
void    signals_handler(void);

//redirections
int    redirect_fd(int *last_input_fd, t_redir *redir, char *file, int redirection_type, t_shell_state *state);
//int     redirection_type(t_command *cmd);
int    apply_redirections(t_command *cmd, t_shell_state *state);
int    collect_and_pipe_hd(char *target, t_shell_state *state);

//sort_envp
void    find_node_by_value(char *x, t_env **currentx, t_env **prevx, t_env **head);
void    update_prev_of_swaped(t_env **current, t_env **prev, t_env **head);
void    update_next_of_swaped( t_env **currentx,  t_env **currenty);
void    swap_nodes_strings(t_env **head, char *x, char *y);
void    sort_list(t_env **env_head);

//linked_lists_handler
char    *get_env_list_value(t_env *env_list, char *key);
char	*expand_line(char *line, t_shell_state *state);


// ------parser to be change-----
// Main parser function
// input: the raw user input line
// output: a linked list of t_command structs (one per command segment)
t_command *parse_input(const char *input);
// Optional: function to free the command list
void free_command_list(t_command *cmd);



#endif
