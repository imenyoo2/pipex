/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:32:04 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:37:05 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// TODO: if n > 1024 this may cause issues

/*
static size_t min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
*/

/*
void *ft_memmove(void *dest, const void *src, size_t n)
{
	char temp[1024];
	size_t copied;

	copied = 0;
	while (copied < n)
	{
		ft_memcpy(temp + copied, src + copied, min(1024, n - copied));
		ft_memcpy(dest + copied, temp, min(1024, n - copied));
		copied += min(1024, n - copied);
	}
	return (dest);
}
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t						counter;
	unsigned char				*destholder;
	const unsigned char			*srcholder;

	destholder = (unsigned char *) dest;
	srcholder = (const unsigned char *) src;
	counter = 0;
	if (destholder > srcholder)
	{
		while (counter < n)
		{
			destholder[n - counter - 1] = srcholder[n - counter - 1];
			counter++;
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
