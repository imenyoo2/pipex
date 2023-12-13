/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:19:49 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:20:00 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>
int main(void)
{
	int start = 0;
	int end;
	
	while (isprint(start) == 0)
		start++;
	end = start;
	while (isprint(end) == 1)
		end++;
	printf("start = %d, end = %d", start, end);
}
*/
