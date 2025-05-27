/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:35:36 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 15:37:49 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
// 

#include <ctype.h>
#include <stdio.h>

// Sample function to modify characters at even indices to uppercase
/*void	to_uppercase_even(unsigned int index, char *c)
{
	if (index % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c = *c - 32; // Convert to uppercase if lowercase and at even index
}

int	main(void)
{
	char str[] = "hello world"; // Test string,	modifiable since it's not a string literal
	// Use ft_striteri to apply to_uppercase_even function
	ft_striteri(str, to_uppercase_even);
	// Print the result
	printf("Modified string: %s\n", str);
	return (0);
}*/
