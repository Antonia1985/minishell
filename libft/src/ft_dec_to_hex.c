/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:16:38 by apavlopo          #+#    #+#             */
/*   Updated: 2024/12/05 15:25:38 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dec_to_hex(unsigned long n, const char *base, int *counter)
{
	if ((n / 16) != 0)
		ft_dec_to_hex(n / 16, base, counter);
	ft_putchar(base[n % 16], counter);
}
