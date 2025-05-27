/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:47:23 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/12 13:48:03 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	s_len;
	size_t	d_len;
	size_t	result;
	size_t	i;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dest);
	result = d_len + s_len;
	i = 0;
	if (destsize <= d_len)
	{
		result = destsize + s_len;
		return (result);
	}
	while (src[i] != '\0' && (d_len + i) < destsize - 1)
	{
		dest[d_len + i] = src[i];
		i++;
	}
	dest[d_len + i] = '\0';
	return (result);
}
// String Concatenate with Size Limit
/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Usage: %s <dest> <src> <destsize>\n", argv[0]);
		return (1);
	}

	// Read command-line arguments
	char dest[100];  // buffer for destination, adjust size as needed
	snprintf(dest, sizeof(dest), "%s", argv[1]);  // copy the initial dest value
	const char *src = argv[2];
	size_t destsize = (size_t)atoi(argv[3]);

	// Run custom ft_strlcat
	size_t result = ft_strlcat(dest, src, destsize);

	// Output results
	printf("Initial dest: \"%s\"\n", argv[1]);
	printf("Source: \"%s\"\n", src);
	printf("Destination size: %zu\n\n", destsize);

	printf("Custom ft_strlcat result:\n");
	printf("Final destination: \"%s\"\n", dest);
	printf("Returned length: %zu\n\n", result);

	return (0);
}*/
