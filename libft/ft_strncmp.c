/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:09:07 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 16:21:48 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	counter;

	if (n == 0)
		return (0);
	counter = 0;
	while ((unsigned char)*s1 - (unsigned char)*s2 == 0
		&& *s1 && *s2 && counter < n - 1)
	{
		s1++;
		s2++;
		counter++;
	}
	if ((unsigned char)*s1 - (unsigned char)*s2 > 0)
		return (1);
	else if ((unsigned char)*s1 - (unsigned char)*s2 < 0)
		return (-1);
	else
		return (0);
}
