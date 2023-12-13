/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:51:42 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/04 17:37:20 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (ft_strlen(s) <= start)
	{
		sub = malloc(1);
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub = malloc(sizeof(char) * (min(len, ft_strlen(&s[start])) + 1));
	if (sub == NULL)
		return (NULL);
	while (i < len && (i + start) < ft_strlen(s))
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
