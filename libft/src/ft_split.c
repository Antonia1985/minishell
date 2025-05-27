/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:16:11 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/16 19:16:16 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*get_next_word(const char **s, char delimiter)
{
	const char	*start;
	char		*word;
	size_t		len;

	while (**s == delimiter)
		(*s)++;
	if (**s == '\0')
		return (ft_strdup(""));
	start = *s;
	while (**s && **s != delimiter)
		(*s)++;
	len = *s - start;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**result;
	int		i;

	words = count_words(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < words)
	{
		result[i] = get_next_word(&s, c);
		i++;
	}
	result[i] = NULL;
	return (result);
}
