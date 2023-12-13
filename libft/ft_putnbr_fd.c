/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:02:40 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/03 15:39:13 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// TODO: im assuming here the integer need to be converted to ascii
// TODO: not tested

/*
	 void ft_putnbr_fd(int n, int fd)
	 {
	 char *str;

	 str = ft_itoa(n);
	 ft_putstr_fd(str, fd);
	 free(str);
	 }
	 */
void	ft_putnbr_fd(int n, int fd)
{
	char	buffer;

	if (n < 0)
	{
		write(fd, "-", 1);
		if (n > -10)
		{
			buffer = '0' + (n * -1);
			write(fd, &buffer, 1);
			return ;
		}
		ft_putnbr_fd(n / -10, fd);
		ft_putnbr_fd((n % -10) * -1, fd);
	}
	else if (n < 10)
	{
		buffer = '0' + n;
		write(fd, &buffer, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
