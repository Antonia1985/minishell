/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:46:32 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/09 12:48:25 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	diff = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
		{
			diff = s1[i] - s2[i];
			return (diff);
		}
		i++;
	}
	return (diff);
}
/*
#include <stdio.h>
#include <stdlib.h>

107
	const char *str1 = argv[1];
	const char *str2 = argv[2];
	size_t n = (size_t)atoi(argv[3]);

	int original_result = strncmp(str1, str2, n);
	int custom_result = ft_strncmp(str1, str2, n);

	printf("Comparing \"%s\" and \"%s\" up to %zu characters:\n", str1, str2,
		n);
	printf("Original strncmp result: %d\n", original_result);
	printf("Custom ft_strncmp result: %d\n", custom_result);

	if (original_result == custom_result)
		printf("Results match!\n");
	else
		printf("Results do not match.\n");

	return (0);
}
*/