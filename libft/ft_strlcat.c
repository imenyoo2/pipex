/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:05:54 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/04 15:54:05 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	return_value;
	size_t	j;

	i = ft_strlen(dst);
	return_value = ft_strlen(src);
	if (i >= dstsize)
		return_value += dstsize;
	else
		return_value += i;
	if (dstsize == 0)
		return (return_value);
	j = 0;
	while (i < dstsize - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (return_value);
}
