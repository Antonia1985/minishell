/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:45:33 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/12 13:45:58 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if ((s - d < 0) && (d < s + n))
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	else
	{
		while (n > i)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*#include <stdio.h>

int	main(void) {
	char buffer1[20] = "1234567890";
	char buffer2[20] = "1234567890";

	// Test case 1: Non-overlapping regions
	printf("Non-overlapping test:\n");
	ft_memmove(buffer1 + 10, buffer1, 5);
	memmove(buffer2 + 10, buffer2, 5);
	printf("ft_memmove result: %s\n", buffer1);
	printf("memmove result   : %s\n", buffer2);
	printf("Match? %s\n\n", strcmp(buffer1, buffer2) == 0 ? "Yes" : "No");

	// Reset buffers for next test
	strcpy(buffer1, "1234567890");
	strcpy(buffer2, "1234567890");

	// Test case 2: Overlapping, dest < src (forward copy)
	printf("Overlapping test (forward copy):\n");
	ft_memmove(buffer1 + 2, buffer1, 5);
	memmove(buffer2 + 2, buffer2, 5);
	printf("ft_memmove result: %s\n", buffer1);
	printf("memmove result   : %s\n", buffer2);
	printf("Match? %s\n\n", strcmp(buffer1, buffer2) == 0 ? "Yes" : "No");

	// Reset buffers for next test
	strcpy(buffer1, "1234567890");
	strcpy(buffer2, "1234567890");

	// Test case 3: Overlapping, dest > src (backward copy)
	printf("Overlapping test (backward copy):\n");
	ft_memmove(buffer1, buffer1 + 2, 5);
	memmove(buffer2, buffer2 + 2, 5);
	printf("ft_memmove result: %s\n", buffer1);
	printf("memmove result   : %s\n", buffer2);
	printf("Match? %s\n\n", strcmp(buffer1, buffer2) == 0 ? "Yes" : "No");

	// Reset buffers for next test
	strcpy(buffer1, "1234567890");
	strcpy(buffer2, "1234567890");

	// Test case 4: Zero bytes copy
	printf("Zero bytes copy test:\n");
	ft_memmove(buffer1, buffer1 + 2, 0);
	memmove(buffer2, buffer2 + 2, 0);
	printf("ft_memmove result: %s\n", buffer1);
	printf("memmove result   : %s\n", buffer2);
	printf("Match? %s\n\n", strcmp(buffer1, buffer2) == 0 ? "Yes" : "No");

	return (0);
}*/
