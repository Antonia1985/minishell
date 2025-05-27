/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:03:19 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 20:04:26 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = c + 32;
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
			std_result = tolower(original);
			custom_result = ft_tolower(original);
			printf(
				"Character: %c | tolower: %c | ft_toupper: %c\n",
				original, std_result, custom_result);
		}
		printf("\n");
	}
	return (0);
}*/
