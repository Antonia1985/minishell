/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:41:24 by apavlopo          #+#    #+#             */
/*   Updated: 2024/10/24 15:48:51 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*#include <stdio.h>

// Function to print buffer contents for verification
void	print_buffer(const unsigned char *buffer, size_t size) {
	for (size_t i = 0; i < size; i++) {
		printf("%02X ", buffer[i]);
	}
	printf("\n");
}
int	main(void) {
	// Test cases
	size_t sizes[] = {10, 5, 0, 15};         // Various buffer sizes
	int fill_values[] = {0, 255, 'A', 127};  // Fill values (0, max byte, 'A',
			and 127)
	size_t num_tests = sizeof(sizes) / sizeof(sizes[0]);

	// Loop through each test case
	for (size_t test = 0; test < num_tests; test++) {
		size_t size = sizes[test];
		int fill_value = fill_values[test];

		// Create and initialize buffers for both custom and original memset
		unsigned char buffer1[size];
		unsigned char buffer2[size];

		memset(buffer1, 0, size);  // Initialize buffers to zero
		memset(buffer2, 0, size);

		// Run original memset and custom ft_memset
		memset(buffer1, fill_value, size);
		ft_memset(buffer2, fill_value, size);

		// Print test case info
		printf("Test #%zu\n", test + 1);
		printf("Size: %zu, Fill Value: %d ('%c')\n", size, fill_value,
			fill_value);

		// Compare and print buffer contents
		printf("Original memset:\n");
		print_buffer(buffer1, size);
		printf("Custom ft_memset:\n");
		print_buffer(buffer2, size);

		// Verify results
		if (memcmp(buffer1, buffer2, size) == 0) {
			printf("PASS\n");
		} else {
			printf("FAIL\n");
		}
		printf("--------------------------------------------------\n");
	}

	return (0);
}*/
/*#include <stdio.h>
#include <stdlib.h> // for atoi

int	main(int argc, char *argv[])
{
	// Check for the correct number of arguments
	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s <string> <char> <num_bytes>\n", argv[0]);
		return (1);
	}

	// Extract the arguments
	char *inputString = argv[1];             // The string to modify
	int charToSet = argv[2][0];              // The character to set
	size_t numBytes = (size_t)atoi(argv[3]); // Number of bytes to set

	// Allocate enough memory to hold the input string
	char *buffer = malloc(strlen(inputString) + 1);
	if (!buffer)
	{
		perror("Failed to allocate memory");
		return (1);
	}

	// Copy the input string to the buffer
	strcpy(buffer, inputString);

	// Call the custom memset function
	ft_memset(buffer, charToSet, numBytes);

	// Print the modified string
	printf("Modified string: %s\n", buffer);

	// Free the allocated memory
	free(buffer);

	return (0);
}*/