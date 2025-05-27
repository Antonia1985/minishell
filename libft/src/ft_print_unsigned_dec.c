/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_dec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:26:49 by apavlopo          #+#    #+#             */
/*   Updated: 2024/12/05 15:33:03 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_unsigned_dec(unsigned int n, int *counter)
{
	char			c;
	unsigned int	max;

	max = 4294967295;
	if (n == max)
		ft_putstr("4294967295", counter);
	else if (n == 0)
		ft_putchar('0', counter);
	else
	{
		c = '\0';
		if ((n / 10) != 0)
			ft_print_unsigned_dec(n / 10, counter);
		c = '0' + (n % 10);
		ft_putchar(c, counter);
	}
}
