/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:24:26 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/20 17:36:26 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert_zero_to_justify(t_format *format)
{
	if ((get_order(format, ZERO) >= get_order(format, JUSTIFY) && format->zero))
	{
		format->justify = format->zero;
		format->flags |= JUSTIFY;
		format->order[get_order(format, JUSTIFY)] = get_order(format, ZERO);
	}
	format->flags &= ~ZERO;
}

void	convert_justify_to_zero(t_format *format)
{
	format->flags &= ~JUSTIFY;
	if (get_order(format, JUSTIFY) >= get_order(format, ZERO) || !format->zero)
	{
		format->zero = format->justify;
		format->flags |= ZERO;
		if (get_order(format, JUSTIFY) >= get_order(format, ZERO))
			format->order[get_order(format, ZERO)] = get_order(format, JUSTIFY);
	}
}

// only use with string, it only work if 0 is after .
void	convert_zero_to_dot(t_format *format)
{
	if (get_order(format, ZERO) == get_order(format, DOT) + 1 && !format->dot)
	{
		format->flags &= ~ZERO;
		format->dot = format->zero;
		if (get_order(format, DOT) >= get_order(format, ZERO))
			format->order[get_order(format, DOT)] = get_order(format, ZERO);
	}
}
