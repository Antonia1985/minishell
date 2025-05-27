/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:47:23 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 13:47:39 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*populated_trimmed(char *trimmed, char const *start, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		trimmed[i] = start[i];
		i++;
	}
	trimmed[length] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	size_t		trimmed_len;
	char		*trimmed;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	start = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (*start && ft_is_in_set(*start, set))
	{
		start++;
	}
	while ((end > start) && (ft_is_in_set(*end, set)))
	{
		end--;
	}
	trimmed_len = end - start + 1;
	trimmed = (char *)malloc(trimmed_len + 1);
	if (!trimmed)
		return (NULL);
	return (populated_trimmed(trimmed, start, trimmed_len));
}
/*#include <stdio.h>

int	main(void) {
	// Test cases
	char *s1 = "  \t\nHello, World!\n\t  ";
	char *set = " \n\t";
	char *trimmed = ft_strtrim(s1, set);
	if (trimmed) {
		printf("Original: \"%s\"\n", s1);
		printf("Set to trim: \"%s\"\n", set);
		printf("Trimmed: \"%s\"\n\n", trimmed);
		free(trimmed);
	}

	// Another test case
	s1 = "###Hello###";
	set = "#";
	trimmed = ft_strtrim(s1, set);
	if (trimmed) {
		printf("Original: \"%s\"\n", s1);
		printf("Set to trim: \"%s\"\n", set);
		printf("Trimmed: \"%s\"\n\n", trimmed);
		free(trimmed);
	}

	// Test with no characters to trim
	s1 = "No trim needed";
	set = "#";
	trimmed = ft_strtrim(s1, set);
	if (trimmed) {
		printf("Original: \"%s\"\n", s1);
		printf("Set to trim: \"%s\"\n", set);
		printf("Trimmed: \"%s\"\n\n", trimmed);
		free(trimmed);
	}

	// Edge case: empty string
	s1 = "";
	set = " \n\t";
	trimmed = ft_strtrim(s1, set);
	if (trimmed) {
		printf("Original: \"%s\"\n", s1);
		printf("Set to trim: \"%s\"\n", set);
		printf("Trimmed: \"%s\"\n\n", trimmed);
		free(trimmed);
	}

	// Edge case: set contains all possible characters
	s1 = "Just text";
	set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	trimmed = ft_strtrim(s1, set);
	if (trimmed) {
		printf("Original: \"%s\"\n", s1);
		printf("Set to trim: \"%s\"\n", set);
		printf("Trimmed: \"%s\"\n\n", trimmed);
		free(trimmed);
	}

	return (0);
}*/
