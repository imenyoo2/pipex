/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:24:36 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 16:25:42 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*returnvalue;

	returnvalue = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			returnvalue = (char *) s;
		s++;
	}
	if (*s == (unsigned char)c)
		returnvalue = (char *) s;
	return (returnvalue);
}
