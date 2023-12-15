/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:50:51 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/15 15:13:16 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_err(const char *format, ...)
{
	va_list	ptr;
	size_t	i;
	size_t	byte_counter;

	i = 0;
	byte_counter = 0;
	va_start(ptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i += ft_convert(&format[i + 1], &byte_counter, ptr);
			if (safe_write("", 0))
        return (-1);
		}
		else
		{
			if (safe_write(&format[i], 1))
        return (-1);
			byte_counter++;
		}
		i++;
	}
	va_end(ptr);
  return (byte_counter);
}
