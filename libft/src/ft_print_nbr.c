/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:26:11 by apavlopo          #+#    #+#             */
/*   Updated: 2024/12/05 15:26:28 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_nbr(int n, int *counter)
{
	char	c;

	if (n == -2147483648)
		ft_putstr("-2147483648", counter);
	else if (n == 0)
		ft_putchar('0', counter);
	else
	{
		c = '\0';
		if (n < 0)
		{
			ft_putchar('-', counter);
			n = -n;
		}
		if ((n / 10) != 0)
			ft_print_nbr(n / 10, counter);
		c = '0' + (n % 10);
		ft_putchar(c, counter);
	}
}
