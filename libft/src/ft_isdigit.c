/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:59:40 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/22 19:03:42 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isdigit(int c)
{
	unsigned int	result;

	result = 0;
	if ((c >= 48) && (c <= 57))
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
		r = ft_isdigit(c);
		i++;
		printf("%i\n", r);
	}
}
*/
