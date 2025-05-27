/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:51:09 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/24 16:52:09 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*#include <stdio.h>
#include <stdlib.h>

int		main(int argc, char *argv[size_tocate memory");
		return (1);
	}

	// Copy the input string into the buffer
	strcpy(buffer, inputString);

	// Print the buffer before using ft_bzero
	printf("Buffer before ft_bzero: '%s'\n", buffer);

	// Call ft_bzero to set the first numBytes bytes to zero
	ft_bzero(buffer, numBytes);

	// Print the modified buffer
	printf("Buffer after ft_bzero: '%s'\n", buffer);

	// Print individual byte values to show the effect of ft_bzero
	for (size_t i = 0; i < bufferSize; i++) {
		printf("buffer[%zu]: %d\n", i, buffer[i]);
	}

	// Clean up
	free(buffer);
	return (0);
}*/