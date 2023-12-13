/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:49:37 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/18 16:20:28 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_conversions(const char *str, t_format *format)
{
	if (*str == 'c')
	{
		format->f = &print_char;
	}
	else if (*str == 's')
		format->f = &print_string;
	else if (*str == 'p')
		format->f = &print_pointer;
	else if (*str == 'd' || *str == 'i')
		format->f = &print_int;
	else if (*str == 'u')
		format->f = &print_unsigned;
	else if (*str == 'x')
		format->f = &print_hex;
	else if (*str == 'X')
		format->f = &print_uhex;
	else if (*str == '%')
		format->f = &print_persent;
	else
	{
		format->conversion = (char)*str;
		format->f = NULL;
	}
}

// returns a value to printf if to indecate if the convertor is valid
// if it's valid, it take controle of printing
size_t	ft_convert(const char *str, size_t *byt_counter, va_list ptr)
{
	t_format	format;
	size_t		return_value;

	init_struct(&format);
	return_value = set_flags(&format, str);
	set_conversions(&str[return_value], &format);
	if (format.f)
	{
		return_value++;
		(format.f)(&format, ptr);
		*byt_counter += format.printed;
		return (return_value);
	}
	else
	{
		manage_flags_int(&format);
		if (format.conversion != '\0')
			return_value += print_the_wierd_stuff(&format);
		*byt_counter += format.printed;
		return (return_value);
	}
}
// TODO: check if the format specifier if invalid
