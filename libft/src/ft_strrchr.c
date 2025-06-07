/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:56:24 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/09 11:57:00 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	//size_t	i;
	int	s_len;
	char	ch;
	char	*ptr;

	//i = 0;
	ch = c;
	s_len = ft_strlen(s);
	while (s_len >= 0)
	{
		if (s[s_len] == ch)
		{
			ptr = (char *)&s[s_len];
			return (ptr);
		}
		if (s_len == 0)
		{
			return (NULL);
		}
		s_len--;
	}
	return (NULL);
}
/*	The strchr() and strrchr()(<-last occurance) functions return a pointer  to  the  matched
	character  or NULL if the character is not found.  The terminating null
	byte is considered part of the string, so that if  c  is  specified  as
	'\0', c = '\0', these functions return a pointer to the terminator.
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
		std_result = strrchr(argv[i], search_char);
		custom_result = ft_strrchr(argv[i], search_char);
		printf("String: \"%s\"\n", argv[i]);
		printf("Standard strchr: %s\n", std_result ? std_result : "NULL");
		printf("Custom ft_strchr: %s\n",
			custom_result ? custom_result : "NULL");
		printf("\n");
	}
	return (0);
}
*/