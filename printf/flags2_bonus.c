/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:05:25 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/20 16:05:33 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*set_space(t_format *format, const char *str)
{
	format->flags |= SPACE;
	set_order(format, SPACE);
	return (str + 1);
}

const char	*set_hashtag(t_format *format, const char *str)
{
	format->flags |= HASHTAG;
	set_order(format, HASHTAG);
	return (str + 1);
}

int	set_flags(t_format *format, const char *str)
{
	const char	*holder; 

	holder = str;
	while (1)
	{
		if ((*holder >= '1' && *holder <= '9'))
			holder = set_justify(format, holder);
		else if (*holder == '-')
			holder = set_minus(format, holder);
		else if (*holder == '0')
			holder = set_zero(format, holder);
		else if (*holder == '.')
			holder = set_dot(format, holder);
		else if (*holder == '+')
			holder = set_plus(format, holder);
		else if (*holder == ' ')
			holder = set_space(format, holder);
		else if (*holder == '#')
			holder = set_hashtag(format, holder);
		else
			break ;
	}
	return (holder - str);
}
