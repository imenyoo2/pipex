/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:18:47 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/20 17:50:13 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pad_left_hex(t_format *format, t_type type, unsigned int nb)
{
	if (format->flags & HASHTAG && nb && format->dot)
	{
		format->dot += 2;
		pad_left(format, type);
		format->dot -= 2;
	}
	else
		pad_left(format, type);
}

void	pad_right(t_format *format, t_type type)
{
	if (format->flags & JUSTIFY && format->flags & MINUS)
		print_nchar(' ', format->justify - get_max_pad(format, type), format);
}

void	pad_left_ptr(t_format *format, t_type type)
{
	format->dot += 2;
	pad_left(format, type);
	format->dot -= 2;
}

size_t	get_max_pad(t_format *format, t_type type)
{
	size_t	dot;
	size_t	zero;
	size_t	printed;

	zero = format->zero * !!(format->flags & ZERO);
	printed = format->printed;
	dot = format->dot * !!(format->flags & DOT) * type;
	return (max(max(zero, printed), dot));
}

void	pad_zero(t_format *format)
{
	if (format->flags & ZERO)
		print_nchar('0', format->zero - format->printed, format);
	if (format->flags & DOT)
		print_nchar('0', format->dot - format->printed, format);
}
