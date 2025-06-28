#include "minishell.h"
#include "libft.h"

char    *get_env_list_value(t_env *env_list, char *key)
{
    while(env_list)
    {
        if(ft_strcmp(env_list->key, key)== 0)
        {
            return(env_list->value);
        }
        env_list = env_list->next;
    }	
    return (NULL);
}

static void	expand_exit_status(char **key, char **value, char *new_line, t_shell_state *state)
{
	free(*key);
	free(*value);
	*key = ft_strdup("?");
	if(!*key)
	{
		free (new_line);
		malloc_failure(state);
	}					
	*value = ft_itoa(g_exit_status);
	if(!*value)
	{
		free(*key);
		free (new_line);
		malloc_failure(state);
	}
}

char	*expand_line(char *line, t_shell_state *state)
{
	char	*key;
	char	*value;
	char	*temp;
	char	*value_temp;
	char	*new_line;
	int		in;
	int		out;
	int		k;
	int		len;
	int		capacity;

	in = 0;
	out = 0;
	capacity = ft_strlen(line) *2 + 1;
	new_line = malloc(capacity);
	key = NULL;
	value = NULL;
	if(!new_line)
		malloc_failure(state);
	while (line[in])
	{
		if(line[in] == '$' && (line[in+1] == '?' || isalnum(line[in+1]) || line[in+1] == '_'))
		{
			if(line[in+1] == '?')
				expand_exit_status(&key, &value, new_line, state);
			else
			{
				free(key);
				free(value);
				temp = ft_strchr(line + in, '$') + 1;
				len = 0;
				while (isalnum(temp[len]) || temp[len] == '_') 
					len++;
				key = ft_substr(temp, 0, len);
				if(!key)
				{
					free (new_line);
					malloc_failure(state);
				}
				value_temp = get_env_list_value(state->env_list, key);
				if(!value_temp)			
					value = ft_strdup("");					
				else
					value = ft_strdup(value_temp);
				if(!value)
				{
					free(key);
					free (new_line);
					malloc_failure(state);
				}
			}
			if(capacity - out < (int)ft_strlen(value) + 1)
			{
				new_line = ft_realloc(new_line, capacity, capacity*2);
				capacity *= 2;	
			}
			k = 0;
			while (value[k])
			{
				new_line[out] = value[k];				
				out++;
				k++;
			}
			in += ft_strlen(key) + 1;			
		}
		else
		{
			new_line[out] = line[in];
			out++;
			in++;
		}
	}
	new_line[out] = '\0';
	if(key)
		free (key);	
	if(value)
		free (value);
	free (line);
	return (new_line);
}
