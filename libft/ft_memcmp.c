/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:30:26 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:30:58 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*holder1;
	unsigned char	*holder2;

	if (n == 0)
		return (0);
	holder1 = (unsigned char *)s1;
	holder2 = (unsigned char *)s2;
	i = 0;
	while (i < n && holder1[i] == holder2[i])
		i++;
	if (i == n)
		i--;
	return (holder1[i] - holder2[i]);
}
