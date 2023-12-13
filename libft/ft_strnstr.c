/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:22:05 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 16:24:18 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while ((i + ft_strlen(needle) - 1) < ft_strlen(haystack)
		&& (i + ft_strlen(needle) - 1) < len)
	{
		if (!ft_strncmp(&haystack[i], needle, ft_strlen(needle)))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
