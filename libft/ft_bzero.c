/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:05:18 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/04 15:14:49 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// TODO: if ft_memset works this should also work

void	ft_bzero(void *s, size_t n)
{
	if (n)
		ft_memset(s, 0, n);
}