/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:53:36 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 16:03:12 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	 int     str_len(char *str)
	 {
	 int     i;

	 i = 0;
	 while (str[i])
	 i++;
	 return (i);
	 }
	 */
static char	*ft_strcpy(char *dest, const char *src)
{
	char	*buffer;

	buffer = dest;
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = *src;
	return (buffer);
}

char	*ft_strdup(const char *s1)
{
	char	*new;

	new = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (new == NULL)
	{
		errno = 132;
		return (NULL);
	}
	ft_strcpy(new, s1);
	return (new);
}
