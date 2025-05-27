/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:01:51 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/24 15:02:23 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}
/*int main(int argc, char * argv[])
{
	// Check if there are enough arguments provided
	if (argc < 2) {
		printf("Usage: %s <string>\n", argv[0]);
		return (1);
	}

	// Loop through each argument and calculate its length
	for (int i = 1; i < argc; i++) {
		size_t len = ft_strlen(argv[i]);
		printf("Length of string \"%s\" (including '\\0'): %zu\n", argv[i],
			len);
	}
}*/