/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:34:43 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/09 15:35:24 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while ((i + j < len) && (big[i + j] == little[j]))
		{
			if (j == little_len - 1)
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	char	*custom_result;
	size_t	len;

	//char *std_result;
	if (argc < 3)
	{
		printf("Usage: %s <big_string> <little_string> [len]\n", argv[0]);
		return (1);
	}
	// If len argument is provided, use it,
		//otherwise default to the length of the big string
	len = (argc == 4) ? atoi(argv[3]) : ft_strlen(argv[1]);
	// Get result from original strstr (it doesn't check the n,
		//length in parameters)
   // std_result = strstr(argv[1], argv[2]);
	// Get result from custom strnstr
	custom_result = ft_strnstr(argv[1], argv[2], len);
	// Print results for comparison
	printf("Big string: \"%s\"\n", argv[1]);
	printf("Little string: \"%s\"\n", argv[2]);
	printf("Length (n): %zu\n", len);
	//printf("\nstrstr result: %s\n", std_result ? std_result : "NULL");
	printf("ft_strnstr result: %s\n", custom_result ? custom_result : "NULL");
	return (0);
}
*/