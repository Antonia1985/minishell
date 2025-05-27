/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:49:07 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/12 13:53:27 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	actual_size;
	char	*buffer;

	actual_size = nmemb * size;
	if (size != 0 && actual_size / size != nmemb)
		return (NULL);
	buffer = (char *)malloc(nmemb * size);
	if (buffer == NULL)
	{
		return (NULL);
	}
	ft_bzero(buffer, actual_size);
	return (buffer);
}
/*int main(void) {
	size_t num_elements = 5;
	int *arr = (int *)ft_calloc(num_elements, sizeof(int));

	// Check if memory allocation was successful
	if (arr == NULL) {
		printf("Memory allocation failed\n");
		return (1);
	}

	// Print the allocated memory to verify it is zeroed out
	printf("Array elements after ft_calloc:\n");
	for (size_t i = 0; i < num_elements; i++) {
		printf("arr[%zu] = %d\n", i, arr[i]); // Each element should be 0
	}

	// Free the allocated memory
	free(arr);
	return (0);
}*/
