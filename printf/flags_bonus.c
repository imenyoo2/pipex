/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:34:33 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/20 16:06:12 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * flags[1]: justify
 * flags[2]: zero
 * flags[4]: dot
 * flags[8]: plus
 * flags[16]: space
 * flags[32]: minus
 * flags[64]: hashtag
 */
#include "ft_printf.h"

// TODO: refactor this
// move the logic to put_nchar
const char	*set_justify(t_format *format, const char *str)
{
	format->justify = ft_atoi(str);
	format->flags |= JUSTIFY;
	set_order(format, JUSTIFY);
	return (skip_num(str));
}

const char	*set_minus(t_format *format, const char *str)
{
	format->flags |= MINUS;
	set_order(format, MINUS);
	return (str + 1);
}

const char	*set_zero(t_format *format, const char *str)
{
	format->flags |= ZERO;
	if (*(str + 1) >= '1' && *(str + 1) <= '9')
		format->zero = (unsigned int) ft_atoi(str);
	else
		return (str + 1);
	set_order(format, ZERO);
	return (skip_num(str));
}

const char	*set_dot(t_format *format, const char *str)
{
	str++;
	format->flags |= DOT;
	set_order(format, DOT);
	if (!(*str >= '0' && *str <= '9'))
	{
		format->dot = 0;
		return (str);
	}
	else
		format->dot = (unsigned int) ft_atoi(str);
	return (skip_num(str));
}

const char	*set_plus(t_format *format, const char *str)
{
	format->flags |= PLUS;
	set_order(format, PLUS);
	return (str + 1);
}
