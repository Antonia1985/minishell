/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:53:36 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 14:54:02 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	size_t	i;
	char	*str;

	s_len = 0;
	i = 0;
	while (s[s_len] != '\0')
	{
		s_len++;
	}
	str = (char *)malloc(s_len + 1);
	if (!str)
		return (NULL);
	while (i < s_len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[s_len] = '\0';
	return (str);
}
/*#include <stdio.h>
#include <stdlib.h>

// Sample function to be applied to each character in the string
char	shift_by_index(unsigned int index, char c)
{
	return (c + index); // Shift character by its index
}

int	main(void)
{
	char	*original;
	char	*result;

	original = "abcdef";
	// Use ft_strmapi to apply shift_by_index function
	result = ft_strmapi(original, shift_by_index);
	if (!result)
	{
		printf("Memory allocation failed.\n");
		return (1);
	}
	// Print the result
	printf("Original: %s\n", original);
	printf("Modified: %s\n", result);
	// Free the allocated memory for result
	free(result);
	return (0);
}*/