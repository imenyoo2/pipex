/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:16:45 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/15 15:09:42 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_nchar(char c, int n, t_format *format)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (c == '0' && !(format->flags & 4)
			&& format->flags & 1 && (i + format->printed >= format->justify))
			break ;
		safe_write(&c, 1);
		i++;
	}
	if (c == '0')
		format->printed += i;
	else
		format->spaces += i;
}

void	put_char(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		safe_write(&c, 1);
		i++;
	}
}

// for - and + printed is incremented in get_print_size/get_print_ssize
void	print_sign(int n, t_format *format)
{
	if (n < 0)
	{
		safe_write("-", 1);
	}
	else if (format->flags & PLUS)
	{
		safe_write("+", 1);
	}
	else if (format->flags & SPACE)
	{
		safe_write(" ", 1);
	}
}

int	print_the_wierd_stuff(t_format *format)
{
	int	i;

	i = 0;
	if (format->flags & ZERO && format->zero)
	{
		put_char('0', format->zero - 1);
		format->printed += format->zero - 1;
	}
	if (format->flags & JUSTIFY && format->justify)
	{
		if (format->conversion && format->flags & MINUS)
		{
			safe_write(&format->conversion, 1);
			format->printed += 1;
			i = 1;
		}
		put_char(' ', format->justify - 1);
		format->printed += format->justify - 1;
	}
	return (i);
}

void	pad_left(t_format *format, t_type type)
{
	if (format->flags & JUSTIFY && !(format->flags & MINUS))
		print_nchar(' ', format->justify - get_max_pad(format, type), format);
}
