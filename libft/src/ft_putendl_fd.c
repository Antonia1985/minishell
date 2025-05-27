/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:59:50 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 16:06:20 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
		write(fd, "\n", 1);
	}
}
/*/
int	main(int argc, char *argv[])
{
	int	i;
	char	*s;
	i = 1;
	while(i < argc)
	{
		s = argv[i];
		ft_putendl_fd(s, 1);
		i++;
	}
	return (0);
}*/