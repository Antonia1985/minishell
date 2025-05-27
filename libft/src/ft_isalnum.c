/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:18:30 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/22 19:23:21 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	unsigned int	result;

	result = 0;
	if (((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)) || ((c >= 48)
			&& (c <= 57)))
	{
		result = 1;
	}
	else
	{
		result = 0;
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
		r = ft_isalnum(c);
		i++;
		printf("%i\n", r);
	}
	return (0);
}
*/
