/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:24:05 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 16:24:59 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_print_number(int n, int fd)
{
	char	c;

	c = '\0';
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	if (n / 10 != 0)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	c = '0' + (n % 10);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	min;
	int	max;

	min = -2147483648;
	max = 2147483647;
	if (n == min)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n == max)
	{
		write(fd, "2147483647", 10);
	}
	else
	{
		if (n == 0)
		{
			write(fd, "0", 1);
		}
		else
		{
			ft_print_number(n, fd);
		}
	}
}
/*int	main(void)
{
	ft_putnbr_fd(570, 1);
	write(1, "\n", 1);

	ft_putnbr_fd(33030, 1);
	write(1, "\n", 1);

	ft_putnbr_fd(0, 1);
	write(1, "\n", 1);

	ft_putnbr_fd(-1, 1);
	write(1, "\n", 1);

	ft_putnbr_fd(-50, 1);
	write(1, "\n", 1);

	ft_putnbr_fd(-2147483648, 1);
	write(1, "\n", 1);

	ft_putnbr_fd(2147483647, 1);
	write(1, "\n", 1);

	ft_putnbr_fd(2147483645, 1);
	write(1, "\n", 1);

	return (0);
}*/