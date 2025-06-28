#include "minishell.h"
#include "libft.h"

static int is_redirect(char *s) {
    return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
         || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"));
}

static void assign_redirect(t_command *cmd, char **tokens, int *i) 
{
    cmd->has_redirection = 1;

    if (!tokens[*i + 1]) {
        print_warning_set_status("minishell: syntax error near unexpected token `%s'\n", 
                                 (char*[]){tokens[*i], NULL}, 2);
        g_exit_status = 2;
        return;
    }

    char *target = ft_strtrim(tokens[++(*i)], " \t\r\n");
    if (!target || target[0] == '\0')
    {
        print_warning_set_status("minishell: missing redirect target\n", NULL, 2);
        g_exit_status = 2;
        return;
    }

    t_redir *new_redir = ft_calloc(1, sizeof(t_redir));
    if (!new_redir)
        return;

    if (!ft_strcmp(tokens[*i - 1], "<"))
        new_redir->type = R_INPUT;
    else if (!ft_strcmp(tokens[*i - 1], ">"))
        new_redir->type = R_OUTPUT;
    else if (!ft_strcmp(tokens[*i - 1], ">>"))
        new_redir->type = R_APPEND;
    else if (!ft_strcmp(tokens[*i - 1], "<<"))
        new_redir->type = R_HEREDOC;
    else
    {
        free(target);
        free(new_redir);
        return;
    }

    new_redir->target = target;
    new_redir->read_fd = -1;
    new_redir->next = NULL;

    if (!cmd->redir_list)
        cmd->redir_list = new_redir;
    else
    {
        t_redir *tmp = cmd->redir_list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_redir;
    }
    (*i)++; 
}

t_command *parse_input(const char *input) {
    if (!input)
        return NULL;

    char **tokens = ft_split(input, ' ');
    if (!tokens)
        return NULL;

    t_command *head = NULL;
    t_command *prev = NULL;
    int i = 0;

    while (tokens[i]) {
        t_command *cmd = ft_calloc(1, sizeof(t_command));
        if (!cmd)
            return NULL;
        cmd->argv = ft_calloc(64, sizeof(char *));
        if (!cmd->argv)
            return NULL;

        // Initialize
        cmd->heredoc = 0;
        cmd->here_doc_read_fd = -1;
        cmd->has_redirection = 0;
        cmd->redir_list = NULL;
        cmd->has_pipe = 0;
        cmd->next = NULL;

        int argc = 0;

        while (tokens[i] && ft_strcmp(tokens[i], "|") != 0) 
        {
            if (is_redirect(tokens[i]))
            {
                assign_redirect(cmd, tokens, &i);
            }
            else 
            {
                char *clean = ft_strtrim(tokens[i], " \t\r\n");
                if (clean && clean[0] != '\0') {
                    cmd->argv[argc++] = clean;
                } else
                    free(clean);
                i++;
            }
        }
        cmd->argv[argc] = NULL;

        if (tokens[i] && !ft_strcmp(tokens[i], "|"))
            cmd->has_pipe = 1;

        if (!head)
            head = cmd;
        else
            prev->next = cmd;
        prev = cmd;

        if (tokens[i] && !ft_strcmp(tokens[i], "|"))
            i++;
    }

    free_array(tokens);
    return head;
}

void free_command_list(t_command *cmd) {
    while (cmd) {
        t_command *next = cmd->next;
        if (cmd->argv) {
            for (int i = 0; cmd->argv[i]; i++)
                free(cmd->argv[i]);
            free(cmd->argv);
        }
        t_redir *redir = cmd->redir_list;
        while (redir) {
            t_redir *rnext = redir->next;
            free(redir->target);
            free(redir);
            redir = rnext;
        }
        free(cmd);
        cmd = next;
    }
}
