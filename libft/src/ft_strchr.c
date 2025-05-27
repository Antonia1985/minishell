/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:11:21 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 20:13:33 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	ch;
	char	*ptr;

	i = 0;
	ch = c;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
		{
			ptr = (char *)&s[i];
			return (ptr);
		}
		i++;
	}
	if (c == '\0')
	{
		ptr = (char *)&s[i];
		return (ptr);
	}
	return (NULL);
}
/*	The strchr() and strrchr() functions return a pointer  to  the  matched
	character  or NULL if the character is not found.  The terminating null
	byte is considered part of the string, so that if  c  is  specified  as
	'\0', these functions return a pointer to the terminator.
*/
/*
#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	int		search_char;
	char	*std_result;
	char	*custom_result;

	if (argc < 3)
	{
		printf("Usage: %s <character to find> <string> [<string>...]\n",
			argv[0]);
		return (1);
	}
	search_char = argv[1][0];
	for (int i = 2; i < argc; i++)
	{
		std_result = strchr(argv[i], search_char);
		custom_result = ft_strchr(argv[i], search_char);
		printf("String: \"%s\"\n", argv[i]);
		printf("Standard strchr: %s\n", std_result ? std_result : "NULL");
		printf("Custom ft_strchr: %s\n",
			custom_result ? custom_result : "NULL");
		printf("\n");
	}
	return (0);
}
*/
