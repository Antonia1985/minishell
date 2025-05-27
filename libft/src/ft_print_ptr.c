/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:20:17 by apavlopo          #+#    #+#             */
/*   Updated: 2024/12/05 18:21:20 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_ptr(unsigned long n, const char *base, int *counter)
{
	if (!n)
	{
		ft_putstr("(nil)", counter);
	}
	else
	{
		ft_putstr("0x", counter);
		ft_dec_to_hex(n, base, counter);
	}
}
