/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers5_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:40:25 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/15 15:09:54 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pad_zero_ptr(t_format *format)
{
	format->printed -= 2;
	format->zero -= 2;
	pad_zero(format);
	format->zero -= 2;
	format->printed += 2;
}

void	pad_zero_hex(t_format *format, unsigned int holder)
{
	if (format->flags & HASHTAG && holder)
	{
		format->printed -= 2;
		format->zero -= 2;
		pad_zero(format);
		format->zero += 2;
		format->printed += 2;
	}
	else
		pad_zero(format);
}

void	put_nstr(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		safe_write(&str[i], 1);
		i++;
	}
}

void	pad_zero_string(t_format *format)
{
	if (format->flags & ZERO)
		print_nchar('0', format->zero - format->printed, format);
}

const char	*skip_num(const char *str)
{
	while (*str >= '0' && *str <= '9')
		str++;
	return (str);
}
