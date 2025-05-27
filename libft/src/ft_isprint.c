/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:03:08 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/22 20:03:18 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int c)
{
	int	result;

	result = 0;
	if ((c > 31) && (c < 127))
	{
		result = 1;
		return (result);
	}
	else
	{
		return (result);
	}
}
/*
#include <stdio.h>

int main() {
    int c;

    // Test with printable characters (e.g., 'A' which is 65)
    c = 'A';
    if (ft_isprint(c)) {
        printf("Character '%c' with ASCII value %d is printable.\n", c, c);
    } else {
        printf("Character '%c' with ASCII value %d is not printable.\n", c, c);
    }

    // Test with non-printable character (e.g., ASCII 10 for newline '\n')
    c = 10;
    if (ft_isprint(c)) {
        printf("Character with ASCII value %d is printable.\n", c);
    } else {
        printf("Character with ASCII value %d is not printable.\n", c);
    }

    // Test with boundary case (ASCII 32, space character)
    c = 32;
    if (ft_isprint(c)) {
        printf("Character with ASCII value %d (space) is printable.\n", c);
    } else {
        printf("Character with ASCII value %d (space) is not printable.\n", c);
    }

    // Test with boundary case (ASCII 126, tilde '~')
    c = 126;
    if (ft_isprint(c)) {
        printf("Character '%c' with ASCII value %d is printable.\n", c, c);
    } else {
        printf("Character '%c' with ASCII value %d is not printable.\n", c, c);
    }

    // Test with a value out of ASCII range (e.g., 200)
    c = 200;
    if (ft_isprint(c)) {
        printf("Character with ASCII value %d is printable.\n", c);
    } else {
        printf("Character with ASCII value %d is not printable.\n", c);
    }

    return 0;
}*/