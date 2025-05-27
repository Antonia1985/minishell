/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:35:53 by apavlopo          #+#    #+#             */
/*   Updated: 2024/12/05 15:36:19 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *s, int *counter)
{
	int	len;

	if (s)
	{
		len = 0;
		while (s[len])
			len++;
		write(1, s, len);
		*counter += len;
	}
	else
	{
		write(1, "(null)", 6);
		*counter += 6;
		return ;
	}
}
