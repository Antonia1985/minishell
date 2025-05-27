/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:32:29 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 19:33:31 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c - 32;
		return (c);
	}
	else
	{
		return (c);
	}
}
/*#include <ctype.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char	original;
	char	std_result;
	char	custom_result;

	if (argc < 2)
	{
		printf("Please provide at least one argument.\n");
		return (1);
	}
	for (int i = 1; i < argc; i++)
	{
		printf("Argument %d: %s\n", i, argv[i]);
		for (int j = 0; argv[i][j] != '\0'; j++)
		{
			original = argv[i][j];
			std_result = toupper(original);
			custom_result = ft_toupper(original);
			printf(
                "Character: 
				%c | Standard toupper: %c | Custom ft_toupper: %c\n", 
                original, std_result, custom_result);
		}
		printf("\n");
	}
	return (0);
}*/
