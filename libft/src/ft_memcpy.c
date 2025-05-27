/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:39:18 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 13:39:44 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d_str;
	const char	*s_str;
	size_t		i;

	d_str = (char *)dest;
	s_str = (const char *)src;
	i = 0;
	while (i < n)
	{
		d_str[i] = s_str[i];
		i++;
	}
	return (dest);
}
/*#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	*src;
	char	*dest;
	char	*dest1;
	size_t	n;

	if (argc != 4)
	{
		printf("Usage: %s <dest> <src> <n>\n", argv[0]);
		return (1);
	}
	n = (size_t)atoi(argv[3]);
	src = argv[2];
	dest = malloc(n + 1);
	dest1 = malloc(n + 1);
	if (!dest || !dest1)
		return (1);

	// Initialize `dest` and `dest1` with the provided destination argument
	strncpy(dest, argv[1], n);
	dest[n] = '\0'; // Null-terminate the string
	strncpy(dest1, argv[1], n);
	dest1[n] = '\0';

	// Perform ft_memcpy and print the result
	ft_memcpy(dest, src, n);
	dest[n] = '\0';
	printf("ft_memcpy result: %s\n", dest);

	// Perform standard memcpy and print the result
	memcpy(dest1, src, n);
	dest1[n] = '\0';
	printf("memcpy result: %s\n", dest1);

	free(dest);
	free(dest1);
	return (0);
}*/
