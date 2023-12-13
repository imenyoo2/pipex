/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:03:15 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:03:17 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skip_white_spaces(const char *str)
{
	while (*str == ' ' || *str == '\n'
		|| *str == '\r' || *str == '\v'
		|| *str == '\f' || *str == '\t')
		str++;
	return (str);
}

static int	get_result(const char *str)
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

/*
#include <stdio.h>
int main(void)
{
printf("expected: 38838, got: %d\n", ft_atoi("38838"));
printf("expected: 8, got: %d\n", ft_atoi("8"));
printf("expected: 0, got: %d\n", ft_atoi("- 8"));
printf("expected: 0, got: %d\n", ft_atoi(""));
printf("expected: -1234, got: %d\n", ft_atoi(" -1234ab567"));
printf("expected: -1234, got: %d\n", ft_atoi(" -0001234ab567"));
printf("expected: -8, got: %d\n", ft_atoi(" -8"));
printf("expected: -7, got: %d\n", ft_atoi(" -7xdf"));
printf("expected: 0, got: %d\n", ft_atoi(" --7xdf"));
printf("expected: 7, got: %d\n", ft_atoi(" +7xdf"));
}
*/
