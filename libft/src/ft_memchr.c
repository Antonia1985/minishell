/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:55:46 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/09 13:56:00 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	ch;
	size_t			i;
	void			*dest;

	src = (unsigned char *)s;
	ch = (unsigned char)c;
	dest = NULL;
	i = 0;
	while (i < n)
	{
		if (src[i] == ch)
		{
			dest = &src[i];
			return (dest);
		}
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	const char	*str = argv[1];
	int			search_char;
	size_t		n;
	void		*original_result;
	void		*custom_result;

	if (argc < 4)
	{
		printf("Usage: %s <string> <character> <n>\n", argv[0]);
		return (1);
	}
	search_char = argv[2][0];
	n = (size_t)atoi(argv[3]);
	// Using the original memchr
	original_result = memchr(str, search_char, n);
	custom_result = ft_memchr(str, search_char, n);
	printf("String: \"%s\"\n", str);
	printf("Character to find: '%c'\n", search_char);
	printf("Number of characters to search: %zu\n", n);
	printf("Original memchr result: %s\n",
		original_result ? (char *)original_result : "NULL");
	printf("Custom ft_memchr result: %s\n",
		custom_result ? (char *)custom_result : "NULL");
	if (original_result == custom_result)
		printf("Results match!\n");
	else
		printf("Results do not match.\n");
	return (0);
}
*/
