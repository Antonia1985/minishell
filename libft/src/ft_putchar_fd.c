/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:33 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/22 15:41:04 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	c;

	i = 1;
	while(i < argc)
	{
		c = *argv[i];
		ft_putchar_fd(c, 1);
		i++;
	}
	return (0);
}
*/