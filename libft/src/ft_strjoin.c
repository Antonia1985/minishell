/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:42:23 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 13:43:08 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	populate_joined(char *joined, const char *s, size_t s_len,
		size_t start)
{
	size_t	j;

	j = 0;
	while (j < s_len)
	{
		joined[start + j] = s[j];
		j++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	len;
	char	*joined;

	if (s1 == NULL)
		len1 = 0;
	if (s2 == NULL)
		len2 = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2 + 1;
	joined = (char *)malloc(len);
	if (!joined)
		return (NULL);
	populate_joined(joined, s1, len1, 0);
	populate_joined(joined, s2, len2, len1);
	joined[len - 1] = '\0';
	return (joined);
}

//Concatenates two strings s1 and s2 into a newly allocated string

/*#include <stdio.h>
#include <stdlib.h>  // For strtoul

int main (int argc, char * argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <string> <start_index> <length>\n", argv[0]);
		return (1);
	}

	char const *s1 = argv[1];

	char const *s2 = argv[2];

	char * result =  ft_strjoin(s1, s2);

	if (result) { // Check if the result is NULL
		printf("Joined string: %s\n", result);
		free(result); // Free the allocated memory
	} else {
		printf("Error: Failed to allocate memory or invalid parameters.\n");
	}

	return (0);
}*/