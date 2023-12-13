/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:50:51 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/11 22:34:49 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_err(int status, const char *format, ...)
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
			if (safe_write(1, "", 0))
				exit(status);
		}
		else
		{
			if (safe_write(1, &format[i], 1))
        exit(status);
			byte_counter++;
		}
		i++;
	}
	va_end(ptr);
  exit(status);
}
