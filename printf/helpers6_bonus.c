/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:29:19 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/20 17:50:33 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	manage_flags_int(t_format *format)
{
	if (format->flags & ZERO)
	{
		if (format->flags & MINUS)
		{
			convert_zero_to_justify(format);
		}
		if (format->flags & DOT)
			convert_zero_to_justify(format);
	}
	if (format->flags & JUSTIFY && format->flags & ZERO)
		convert_justify_to_zero(format);
}

void	manage_flags_string(t_format *format)
{
	if (format->flags & MINUS)
	{
		if (format->flags & ZERO)
			convert_zero_to_justify(format);
	}
	if (format->flags & JUSTIFY)
	{
		if (format->flags & ZERO)
			convert_justify_to_zero(format);
	}
}

void	set_order(t_format *format, t_flag flag)
{
	int	i;
	int	holder;

	i = 0;
	holder = (int) flag;
	while (holder)
	{
		holder = holder >> 1;
		i++;
	}
	i--;
	(format->order)[i] = format->current_order;
	format->current_order += 1;
}

size_t	get_order(t_format *format, t_flag flag)
{
	int	i;
	int	holder;

	i = 0;
	holder = (int) flag;
	while (holder)
	{
		holder = holder >> 1;
		i++;
	}
	i--;
	return ((format->order)[i]);
}

void	init_struct(t_format *format)
{
	int	i;

	format->flags = 0;
	format->printed = 0;
	format->justify = 0;
	format->zero = 0;
	format->dot = 0;
	format->spaces = 0;
	format->current_order = 0;
	i = 0;
	while (i < 7)
	{
		(format->order)[i] = 0;
		i++;
	}
}
