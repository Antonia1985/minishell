/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:36 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 13:50:07 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	src_l;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	src_l = ft_strlen(s);
	if (start >= src_l)
	{
		substr = malloc(1);
		substr[0] = '\0';
		return (substr);
	}
	if (src_l < (start + len))
		len = src_l - start;
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	while (i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

/*#include <stdio.h>
#include <stdlib.h>  // For strtoul

int main (int argc, char * argv[])
{
	if (argc != 4)
	{
		printf("Usage: %s <string> <start_index> <length>\n", argv[0]);
		return (1);
	}

	char const *s = argv[1];

	unsigned int start =(unsigned int) strtoul(argv[2], NULL, 10);

	size_t len =  strtoul(argv[3], NULL, 10);
		// Converts argv[3] to an unsigned integer

	char * result =  ft_substr(s, start, len);

	if (result) { // Check if the result is NULL
		printf("Substring: %s\n", result);
		free(result); // Free the allocated memory
	} else {
		printf("Error: Failed to allocate memory or invalid parameters.\n");
	}

	return (0);
}*/
