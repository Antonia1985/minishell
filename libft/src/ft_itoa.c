/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:38:09 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/07 13:38:32 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*populate_string(char *dest, char *src)
{
	size_t	i;

	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*string_edge_case(int n, int min, int max)
{
	size_t	i;
	char	*str_num;

	i = 0;
	if (n == min)
	{
		str_num = (char *)malloc(12);
		return (populate_string(str_num, "-2147483648"));
	}
	else if (n == max)
	{
		str_num = (char *)malloc(11);
		return (populate_string(str_num, "2147483647"));
	}
	else if (n == 0)
	{
		str_num = (char *)malloc(2);
		str_num[i++] = '0';
		str_num[i] = '\0';
		return (str_num);
	}
	return (NULL);
}

static int	length_from_integer(int n)
{
	size_t	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*integer_to_string(char *dest, int n, size_t start, size_t str_len)
{
	size_t	i;
	char	swap;

	i = start;
	while (n != 0)
	{
		dest[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	dest[i] = '\0';
	while (start < (str_len + start) / 2)
	{
		swap = dest[start];
		dest[start] = dest[str_len - 1];
		dest[str_len - 1] = swap;
		start++;
		str_len--;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	size_t	start;
	size_t	str_len;
	char	*str_num;
	char	sign;

	sign = '+';
	start = 0;
	str_len = 0;
	if (n == -2147483648 || n == 2147483647 || n == 0)
		return (string_edge_case(n, -2147483648, 2147483647));
	if (n < 0)
	{
		sign = '-';
		n = -n;
		start++;
	}
	str_len = length_from_integer(n);
	if (sign == '-')
		str_len++;
	str_num = (char *)malloc(str_len + 1);
	str_num = integer_to_string(str_num, n, start, str_len);
	if (sign == '-')
		str_num[0] = sign;
	return (str_num);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-2147483648)); // Prints "-2147483648"
	printf("%s\n", ft_itoa(2147483647));  // Prints "2147483647"
	printf("%s\n", ft_itoa(0));           // Prints "0"
	printf("%s\n", ft_itoa(-123));        // Prints "-123"
	printf("%s\n", ft_itoa(456));         // Prints "456"
	return (0);
}*/