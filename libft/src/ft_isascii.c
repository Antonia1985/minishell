/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:26:47 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/22 19:43:58 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isascii(int c)
{
	int	result;

	result = 1;
	if ((c > 127) || (c < 0))
	{
		result = 0;
		return (result);
	}
	else
	{
		return (result);
	}
}

/*
#include <stdio.h>

int	main(void) {
	int c;

	// Test with an ASCII character (e.g., 'A' which is 65)
	c = 'A';
	if (ft_isascii(c)) {
		printf("Character '%c' with ASCII value %d   is ASCII.\n", c, c);
	} else {
		printf("Character '%c' with ASCII value %d  is NOT ASCII.\n", c, c);
	}

	// Test with a non-ASCII character (e.g., 200)
	c = 200;
	if (ft_isascii(c)) {
		printf("Character '%c' with ASCII value %d  is ASCII.\n", c, c);
	} else {
		printf("Character '%c' with ASCII value %d  is NOT ASCII.\n", c, c);
	}

	// Test with boundary case (127, which is the last valid ASCII character)
	c = 127;
	if (ft_isascii(c)) {
		printf("Character '%c' with ASCII value %d  is ASCII.\n", c, c);
	} else {
		printf("Character '%c' with ASCII value %d  is NOT ASCII.\n", c, c);
	}

	// Test with boundary case (0, which is the first valid ASCII character)
	c = 0;
	if (ft_isascii(c)) {
		printf("Character '%c' with ASCII value %d  is ASCII.\n", c, c);
	} else {
		printf("Character '%c' with ASCII value %d  is NOT ASCII .\n", c, c);
	}

	c = -1;
	if (ft_isascii(c)) {
		printf("Character '%c' with ASCII value %d  is ASCII.\n", c, c);
	} else {
		printf("Character '%c' with ASCII value %d  is NOT ASCII.\n", c, c);
	}



	return (0);
}
*/