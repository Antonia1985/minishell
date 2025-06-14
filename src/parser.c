#include "minishell.h"
#include "libft.h"

// Helpers
static int is_redirect(char *s) {
    return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
         || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"));
}

static void assign_redirect(t_command *cmd, char **tokens, int *i) {
    // Mark that this command has a redirection
    cmd->has_redirection = 1;

    if (!ft_strcmp(tokens[*i], "<")) {
        cmd->infile = ft_strdup(tokens[++(*i)]);
    } else if (!ft_strcmp(tokens[*i], ">")) {
        cmd->outfile = ft_strdup(tokens[++(*i)]);
        cmd->append = 0;
    } else if (!ft_strcmp(tokens[*i], ">>")) {
        cmd->outfile = ft_strdup(tokens[++(*i)]);
        cmd->append = 1;
    } else if (!ft_strcmp(tokens[*i], "<<")) {
        cmd->heredoc = 1;
        cmd->heredoc_delim = ft_strdup(tokens[++(*i)]);
    }
    (*i)++;
}

// Parses the input string into a linked list of t_command
// Each t_command may have arguments, redirections, heredoc, and pipe flag

t_command *parse_input(const char *input) {
    if (!input)
        return NULL;

    // Split the raw input on spaces (simple tokenizer)
    char **tokens = ft_split(input, ' ');
    if (!tokens)
        return NULL;

    t_command *head = NULL;
    t_command *prev = NULL;
    int i = 0;

    while (tokens[i]) {
        t_command *cmd = ft_calloc(1, sizeof(t_command));
        if (!cmd) return NULL;
        cmd->argv = ft_calloc(64, sizeof(char *)); // reserve up to 64 args

        // Initialize fields and flags
        cmd->infile = NULL;
        cmd->outfile = NULL;
        cmd->append = 0;
        cmd->heredoc = 0;
        cmd->heredoc_delim = NULL;
        cmd->has_redirection = 0;
        cmd->has_pipe = 0;
        cmd->next = NULL;

        int argc = 0;
        // Collect args and redirections until a pipe or end
        while (tokens[i] && ft_strcmp(tokens[i], "|") != 0) {
            if (is_redirect(tokens[i])) {
                assign_redirect(cmd, tokens, &i);
            } else {
                cmd->argv[argc++] = ft_strdup(tokens[i++]);
            }
        }
        cmd->argv[argc] = NULL;

        // If we stopped at a pipe, note it
        if (tokens[i] && !ft_strcmp(tokens[i], "|")) {
            cmd->has_pipe = 1;
        }

        // Link into list
        if (!head)
            head = cmd;
        else
            prev->next = cmd;
        prev = cmd;

        // Skip over the '|' token
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
        free(cmd->infile);
        free(cmd->outfile);
        free(cmd->heredoc_delim);
        free(cmd);
        cmd = next;
    }
}
