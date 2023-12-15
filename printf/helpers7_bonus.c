/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers7_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:33:10 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/15 15:10:31 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	manage_flags_hex(t_format *format, unsigned int nb)
{
	manage_flags_int(format);
	if (format->flags & HASHTAG && nb)
		format->printed += 2;
}

int	safe_write(const char *ptr, int n)
{
	static int	stop_signal = 0;

	if (!stop_signal && n)
	{
		if (write(2, ptr, n) == -1)
			stop_signal = 1;
	}
	return (stop_signal);
}

void	manage_flags_char(t_format *format)
{
	if (format->flags & MINUS)
		convert_zero_to_justify(format);
	if (format->flags & JUSTIFY)
	{
		if (format->flags & ZERO)
			convert_justify_to_zero(format);
	}
}
