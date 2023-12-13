/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:06:06 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:06:18 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_overflow(size_t a, size_t b)
{
	size_t	result;

	if (a == 0 || b == 0) 
		return (0);
	result = a * b;
	if (a == result / b)
		return (0);
	else
		return (1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (is_overflow(nmemb, size))
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}
