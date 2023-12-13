/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:20:11 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:20:50 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_malloc_size(int n)
{
	int		size;
	long	holder;

	size = 1;
	holder = n;
	if (holder < 0)
	{
		holder = -holder;
		size++;
	}
	holder = holder / 10;
	while (holder)
	{
		holder = holder / 10;
		size++;
	}
	return (size);
}

static int	int2str(char *buffer, long n, int index)
{
	if (n < 0)
	{
		buffer[index] = '-';
		n = -n;
		index++;
	}
	if (n < 10)
		buffer[index] = '0' + n;
	else
	{
		index = int2str(buffer, n / 10, index);
		buffer[index] = '0' + (n % 10);
	}
	return (index + 1);
}

char	*ft_itoa(int n)
{
	int		malloc_size;
	char	*result;

	malloc_size = get_malloc_size(n);
	result = malloc((malloc_size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	int2str(result, (long) n, 0);
	result[malloc_size] = '\0';
	return (result);
}
