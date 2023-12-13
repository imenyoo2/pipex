/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:28:12 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:30:01 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*holder;
	size_t			i;

	holder = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (holder[i] == (unsigned char) c)
			return ((void *) &holder[i]);
		i++;
	}
	return (NULL);
}
