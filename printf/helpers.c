/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:32:46 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/20 16:13:38 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putsnbr_base(ssize_t nbr, const char *base)
{
	int	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nbr < 0)
	{
		if (nbr > (-1 * base_len))
			safe_write(1, &base[nbr * -1], 1);
		else
		{
			ft_putnbr_base(nbr / (base_len * -1), base);
			ft_putnbr_base((nbr % (base_len * -1)) * -1, base);
		}
	}
	else if (nbr < base_len)
		safe_write(1, &base[nbr], 1);
	else
	{
		ft_putnbr_base(nbr / base_len, base);
		ft_putnbr_base(nbr % base_len, base);
	}
}

void	ft_putnbr_base(size_t nbr, const char *base)
{
	size_t	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nbr < base_len)
		safe_write(1, &base[nbr], 1);
	else
	{
		ft_putnbr_base(nbr / base_len, base);
		ft_putnbr_base(nbr % base_len, base);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

unsigned int	get_print_size(size_t nb, unsigned int baselen,
		t_format *format)
{
	unsigned int	counter;

	counter = 1;
	if (!(format->flags & DOT && !format->dot && !nb))
	{
		nb = nb / baselen;
		while (nb)
		{
			nb = nb / baselen;
			counter++;
		}
	}
	else
		counter--;
	return (counter);
}

unsigned int	get_print_ssize(ssize_t nb, unsigned int baselen,
		t_format *format)
{
	unsigned int	counter;

	counter = 1;
	if (nb < 0)
	{
		counter++;
		if (format->flags & DOT && format->dot)
			format->dot += 1;
	}
	if ((format->flags & PLUS || format->flags & SPACE) && nb >= 0)
	{
		counter++;
		if (format->flags & DOT && format->dot)
			format->dot += 1;
	}
	if (!(format->flags & DOT && !format->dot && !nb))
	{
		nb = nb / baselen;
		while (nb && counter++)
			nb = nb / baselen;
	}
	else
		counter--;
	return (counter);
}
