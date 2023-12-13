/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:13:16 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/20 17:49:56 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*skip_white_spaces(const char *str)
{
	while (*str == ' ' || *str == '\n'
		|| *str == '\r' || *str == '\v'
		|| *str == '\f' || *str == '\t')
		str++;
	return (str);
}

int	get_result(const char *str)
{
	int	result;

	result = 0;
	if (*str >= '0' && *str <= '9')
	{
		result += *str - '0';
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	minus_counter;
	int	result;

	str = skip_white_spaces(str);
	minus_counter = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus_counter++;
		str++;
	}
	result = get_result(str);
	if (minus_counter % 2)
		return (result * -1);
	else
		return (result);
}

size_t	min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

size_t	max(size_t a, size_t b)
{
	if (a < b)
		return (b);
	else
		return (a);
}
