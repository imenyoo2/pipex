/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:43:43 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/15 15:11:10 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unsigned(t_format *format, va_list ptr)
{
	unsigned int	holder;
	char			*base;

	base = "0123456789";
	holder = va_arg(ptr, int);
	format->printed += get_print_size((size_t) holder,
			(unsigned int) ft_strlen(base), format);
	manage_flags_int(format);
	pad_left(format, INT);
	pad_zero(format);
	if (!(format->flags & DOT && !format->dot && !holder))
		ft_putnbr_base((size_t) holder, base);
	pad_right(format, INT);
	format->printed += format->spaces;
}

void	print_hex(t_format *format, va_list ptr)
{
	unsigned int	holder;
	char			*base;

	manage_flags_int(format);
	base = "0123456789abcdef";
	holder = va_arg(ptr, int);
	format->printed += get_print_size((size_t) holder,
			(unsigned int) ft_strlen(base), format);
	manage_flags_hex(format, holder);
	pad_left_hex(format, INT, holder);
	if (format->flags & HASHTAG && holder)
		safe_write("0x", 2);
	pad_zero_hex(format, holder);
	if (!(format->flags & DOT && !format->dot && !holder))
		ft_putnbr_base((size_t) holder, base);
	pad_right(format, INT);
	format->printed += format->spaces;
}

void	print_uhex(t_format *format, va_list ptr)
{
	unsigned int	holder;
	char			*base;

	base = "0123456789ABCDEF";
	holder = va_arg(ptr, int);
	format->printed += get_print_size((size_t) holder,
			(unsigned int) ft_strlen(base), format);
	manage_flags_hex(format, holder);
	pad_left_hex(format, INT, holder);
	if (format->flags & HASHTAG && holder)
		safe_write("0X", 2);
	pad_zero_hex(format, holder);
	if (!(format->flags & DOT && !format->dot && !holder))
		ft_putnbr_base((size_t) holder, base);
	pad_right(format, INT);
	format->printed += format->spaces;
}

void	print_persent(t_format *format, va_list ptr)
{
	(void) ptr;
	manage_flags_string(format);
	format->printed += 1;
	pad_left(format, STRING);
	pad_zero_string(format);
	safe_write("%", 1);
	pad_right(format, STRING);
	format->printed += format->spaces;
}
