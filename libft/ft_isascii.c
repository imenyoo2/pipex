/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:19:09 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:19:16 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	printf("expected %d, got %d\n", isascii(128), ft_isascii(128));
	printf("expected %d, got %d\n", isascii(127), ft_isascii(127));
}
*/
