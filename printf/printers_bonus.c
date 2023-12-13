/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:33:54 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/20 17:44:11 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(t_format *format, va_list ptr)
{
	char	holder;

	manage_flags_char(format);
	holder = va_arg(ptr, int);
	format->printed++;
	pad_left(format, STRING);
	pad_zero_string(format);
	safe_write(1, &holder, 1);
	pad_right(format, INT);
	format->printed += format->spaces;
}

static void	handle_null_string(t_format *format)
{
	size_t	len;

	len = 6;
	if (format->flags & DOT)
		len = min(6, (size_t) format->dot);
	format->printed += len;
	pad_left(format, STRING);
	pad_zero_string(format);
	safe_write(1, "(null)", len);
	pad_right(format, STRING);
	format->printed += format->spaces;
}

void	print_string(t_format *format, va_list ptr)
{
	size_t	len;
	char	*holder;

	manage_flags_string(format);
	holder = va_arg(ptr, char *);
	if (holder == NULL)
	{
		handle_null_string(format);
		return ;
	}
	len = ft_strlen(holder);
	if (format->flags & DOT)
		len = min(len, (size_t)format->dot);
	format->printed += len;
	pad_left(format, STRING);
	pad_zero_string(format);
	put_nstr(holder, len);
	pad_right(format, STRING);
	format->printed += format->spaces;
}

void	print_pointer(t_format *format, va_list ptr)
{
	void	*holder;
	char	*base;

	manage_flags_int(format);
	base = "0123456789abcdef";
	holder = va_arg(ptr, void *);
	format->printed += get_print_size((size_t) holder,
			(unsigned int)ft_strlen(base), format);
	format->printed += 2;
	pad_left_ptr(format, INT);
	safe_write(1, "0x", 2);
	pad_zero_ptr(format);
	if (!(format->flags & DOT && !format->dot && !holder))
		ft_putnbr_base((size_t) holder, base);
	pad_right(format, INT);
	format->printed += format->spaces;
}

void	print_int(t_format *format, va_list ptr)
{
	int		holder;
	char	*base;

	manage_flags_int(format);
	base = "0123456789";
	holder = va_arg(ptr, int);
	format->printed += get_print_ssize((ssize_t) holder,
			(unsigned int) ft_strlen(base), format);
	pad_left(format, INT);
	print_sign(holder, format);
	pad_zero(format);
	if (!(format->flags & DOT && !format->dot && !holder))
		ft_putsnbr_base((ssize_t) holder, base);
	pad_right(format, INT);
	format->printed += format->spaces;
}
