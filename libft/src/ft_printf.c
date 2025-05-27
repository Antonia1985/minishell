/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:18:04 by apavlopo          #+#    #+#             */
/*   Updated: 2024/11/30 15:18:17 by apavlopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	conversion_cases(char conversion_char, va_list args, int *counter)
{
	const char	base_low[16] = "0123456789abcdef";
	const char	base_up[16] = "0123456789ABCDEF";

	if (conversion_char == 'c')
		ft_putchar((char)va_arg(args, int), counter);
	else if (conversion_char == 's')
		ft_putstr(va_arg(args, char *), counter);
	else if (conversion_char == 'p')
		ft_print_ptr(va_arg(args, unsigned long), base_low, counter);
	else if (conversion_char == 'd' || conversion_char == 'i')
		ft_print_nbr(va_arg(args, int), counter);
	else if (conversion_char == 'u')
		ft_print_unsigned_dec(va_arg(args, unsigned int), counter);
	else if (conversion_char == 'x')
		ft_dec_to_hex((unsigned long)va_arg(args, unsigned int), base_low,
			counter);
	else if (conversion_char == 'X')
		ft_dec_to_hex((unsigned long)va_arg(args, unsigned int), base_up,
			counter);
	else if (conversion_char == '%')
		ft_putchar('%', counter);
	else
		ft_putchar(conversion_char, counter);
}

int	ft_printf(const char *format, ...)
{
	int		counter;
	va_list	args;

	va_start(args, format);
	counter = 0;
	if (!format)
		return (0);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			conversion_cases(*format, args, &counter);
		}
		else
			ft_putchar((char)*format, &counter);
		format++;
	}
	va_end(args);
	return (counter);
}
// --- %x ---
// The %x format specifier in printf is used to print
// an unsigned integer in lowercase hexadecimal format.
// It expects an input of type unsigned int