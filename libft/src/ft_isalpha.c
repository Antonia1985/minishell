/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:37:05 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/24 14:00:47 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalpha(int c)
{
	unsigned int	result;

	result = 0;
	if (((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)))
	{
		result = 1;
	}
	return (result);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	c;
	int	r;

	i = 1;
	while(i < argc)
	{
		c = *argv[i];
		r = ft_isalpha(c);
		i++;
		printf("%i\n", r);
	}
	return (0);
}
*/