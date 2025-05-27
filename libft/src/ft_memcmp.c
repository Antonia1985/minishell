/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:56:52 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/09 15:01:22 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	size_t			i;
	int				result;

	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	i = 0;
	result = 0;
	while (i < n)
	{
		if (src1[i] != src2[i])
		{
			result = src1[i] - src2[i];
			return (result);
		}
		i++;
	}
	return (result);
}
/*
#include <stdio.h>

int	main(void)
{
	// Example 1: Identical byte arrays
	char s1[] = "Hello World!";
	char s2[] = "Hello World!";
	printf("Comparing identical strings:\n");
	printf("Original memcmp: %d\n", memcmp(s1, s2, strlen(s1)));
	printf("Custom memcmp: %d\n\n", ft_memcmp(s1, s2, strlen(s1)));

	// Example 2: Different byte arrays
	char s3[] = "Hello World!";
	char s4[] = "Hello there!";
	printf("Comparing different strings:\n");
	printf("Original memcmp: %d\n", memcmp(s3, s4, strlen(s3)));
	printf("Custom memcmp: %d\n\n", ft_memcmp(s3, s4, strlen(s3)));

	// Example 3: First n bytes are identical, the rest are different
	char s5[] = "Hello";
	char s6[] = "Hello123";
	printf("Comparing strings with first n bytes identical:\n");
	printf("Original memcmp: %d\n", memcmp(s5, s6, 5));
	printf("Custom memcmp: %d\n\n", ft_memcmp(s5, s6, 5));

	// Example 4:
	char s7[] = "Hello World!";
	char s8[] = "Hello Beautiful World!";
	printf("Comparing substrings of different lengths:\n");
	printf("Original memcmp: %d\n", memcmp(s7, s8, 10));
	printf("Custom memcmp: %d\n\n", ft_memcmp(s7, s8, 10));

	return (0);
}*/